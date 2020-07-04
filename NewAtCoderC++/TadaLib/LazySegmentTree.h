#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <stack>
#include <complex>
#include <functional>
#include <tuple>

using namespace std;

#define Rep(i,a,b) for(ll i = a; i < b; ++i)
#define rep(i,b) Rep(i,0,b)
#define allof(a) (a).begin(), (a).end()

using ll = long long;

constexpr int inf = 1e9 + 7;
constexpr ll infll = 1ll << 60ll;
constexpr ll mod = 1e9 + 7;
// 0~3までは右左下上 4~7までは斜め
constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };

template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

// @category セグメント木 (Segment Tree)
// @title 遅延伝播セグメント木 (Lazy Segment Tree)
template <typename MonoidType, typename OperatorType>
struct LazySegmentTree {
    using MMtoM = function< MonoidType(MonoidType, MonoidType) >;
    using OOtoO = function< OperatorType(OperatorType, OperatorType) >;
    using MOtoM = function< MonoidType(MonoidType, OperatorType) >;
    using OItoO = function< OperatorType(OperatorType, int) >;

    // node, lazy, update flag (for lazy), identity element
    int n;
    vector<MonoidType> node;
    vector<OperatorType> lazy;
    vector<bool> need_update;
    MonoidType E0;
    OperatorType E1;

    // update / combine / lazy / accumulate function
    MOtoM upd_f;
    MMtoM cmb_f;
    OOtoO lzy_f;
    OItoO acc_f;

    // 直接構築 a is 0-indexed
    void set(int i, const MonoidType& v) { node[n - 1 + i] = v; }
    void build() {
        for (int i = n - 2; i >= 0; --i) {
            node[i] = cmb_f(node[i * 2 + 1], node[i * 2 + 2]);
        }
    }

    // initialize
    LazySegmentTree() {}
    LazySegmentTree(int n_, MonoidType E0_, OperatorType E1_,
        MOtoM upd_f_, MMtoM cmb_f_, OOtoO lzy_f_, OItoO acc_f_,
        MonoidType unity_monoid, OperatorType unity_operation) :
        E0(E0_), E1(E1_),
        upd_f(upd_f_), cmb_f(cmb_f_), lzy_f(lzy_f_), acc_f(acc_f_) {

        n = 1; while (n < n_) n *= 2;

        node = vector<MonoidType>(2 * n - 1, unity_monoid);
        lazy = vector<OperatorType>(2 * n - 1, unity_operation);
        need_update = vector<bool>(2 * n - 1, false);
    }

    void eval(int k, int l, int r) {
        if (!need_update[k]) return;
        node[k] = upd_f(node[k], acc_f(lazy[k], r - l));
        if (r - l > 1) {
            lazy[2 * k + 1] = lzy_f(lazy[2 * k + 1], lazy[k]);
            lazy[2 * k + 2] = lzy_f(lazy[2 * k + 2], lazy[k]);
            need_update[2 * k + 1] = need_update[2 * k + 2] = true;
        }
        lazy[k] = E1;
        need_update[k] = false;
    }

    void update(int a, int b, OperatorType x, int l, int r, int k) {
        eval(k, l, r);
        if (b <= l or r <= a) return;
        if (a <= l and r <= b) {
            lazy[k] = lzy_f(lazy[k], x);
            need_update[k] = true;
            eval(k, l, r);
        }
        else {
            int mid = (l + r) / 2;
            update(a, b, x, l, mid, 2 * k + 1);
            update(a, b, x, mid, r, 2 * k + 2);
            node[k] = cmb_f(node[2 * k + 1], node[2 * k + 2]);
        }
    }

    MonoidType query(int a, int b, int l, int r, int k) {
        if (b <= l or r <= a) return E0;
        eval(k, l, r);
        if (a <= l and r <= b) return node[k];
        int mid = (l + r) / 2;
        MonoidType vl = query(a, b, l, mid, 2 * k + 1);
        MonoidType vr = query(a, b, mid, r, 2 * k + 2);
        return cmb_f(vl, vr);
    }

    // update [a, b)-th element (applied value, x)
    void update(int a, int b, OperatorType x) {
        update(a, b, x, 0, n, 0);
    }

    // range query for [a, b)
    MonoidType query(int a, int b) {
        return query(a, b, 0, n, 0);
    }

    void dump() {
        fprintf(stderr, "[lazy]\n");
        for (int i = 0; i < 2 * n - 1; i++) {
            if (i == n - 1) fprintf(stderr, "xxx ");
            if (lazy[i] == E1) fprintf(stderr, "  E ");
            else fprintf(stderr, "%3d ", lazy[i]);
        }
        fprintf(stderr, "\n");

        fprintf(stderr, "[node]\n");
        for (int i = 0; i < 2 * n - 1; i++) {
            if (i == n - 1) fprintf(stderr, "xxx ");
            if (node[i] == E0) fprintf(stderr, "  E ");
            else fprintf(stderr, "%3d ", node[i]);
        }
        fprintf(stderr, "\n");
    }
};

int main() {

    int n;
    string x;
    int q;
    cin >> n >> x >> q;

    using M = ll; // モノイドの型
    using O = ll; // 作用の型
    auto fmo = [](M m, O o) -> M { return o; }; // モノイドをどう変化させるか
    auto fmm = [](M m1, M m2) -> M { return m1 + m2; }; // モノイドとモノイドの演算
    auto foo = [](O o1, O o2) -> O { return o2; }; // 作用の合成
    auto foi = [](O o, int x) -> O {return o * x; };
    M em = 0; // モノイドの単位元
    O eo = 0; // 作用の単位元
    LazySegmentTree<M, O> seg_f(n, em, eo, fmo, fmm, foo, foi, 0, 0);
    LazySegmentTree<M, O> seg_g(n - 1, em, eo, fmo, fmm, foo, foi, 0, 0);

    rep(i, n) {
        int c = x[i] - '0';
        seg_f.set(i, c);
        if (i != n - 1) {
            seg_g.set(i, c * (x[i + 1] - '0'));
        }
    }
    seg_f.build();
    seg_g.build();

    vector<int> ans(q);

    //cout << " ";
    //rep(i, n - 1) {
    //    cout << seg_g.query(i, i + 1) << " ";
    //}
    //cout << endl;
    rep(i, q) {
        int l, r, b;
        cin >> l >> r >> b;
        seg_f.update(l - 1, r, b);
        seg_g.update(l - 1, r - 1, b);
        // はじを変える
        seg_g.update(l - 2, l - 1, b * seg_f.query(l - 2, l - 1));
        seg_g.update(r - 1, r, b * seg_f.query(r, r + 1));
        rep(i, n) {
            cout << seg_f.query(i, i + 1) << " ";
        }
        cout << endl;
        cout << " ";
        rep(i, n - 1) {
            cout << seg_g.query(i, i + 1) << " ";
        }
        cout << endl;
        ans[i] = seg_f.query(0, n) - seg_g.query(0, n - 1);
        cout << seg_f.query(0, n) << " " << seg_g.query(0, n - 1) << endl;
    }

    for (auto a : ans) cout << a << endl;

    return 0;
}

int main() {

    int n, m;
    cin >> n >> m;

    using M = ll; // モノイドの型
    using O = ll; // 作用の型
    auto fmo = [](M m, O o) -> M { return max(m, o); }; // モノイドをどう変化させるか
    auto fmm = [](M m1, M m2) -> M { return max(m1, m2); }; // モノイドとモノイドの演算
    auto foo = [](O o1, O o2) -> O { return max(o1, o2); }; // 作用の合成
    auto foi = [](O o, int x) -> O {return o * x; };
    M em = 0; // モノイドの単位元
    O eo = 0; // 作用の単位元
    LazySegmentTree<M, O> seg(n, em, eo, fmo, fmm, foo, foi, 0, 0);

    rep(i, m) {
        int t, l, r;
        cin >> t >> l >> r;

        seg.update(l - 1, r, t);
    }

    ll ans = 0LL;
    rep(i, n) ans += seg.query(i, i + 1);

    cout << ans << endl;

    return 0;
}