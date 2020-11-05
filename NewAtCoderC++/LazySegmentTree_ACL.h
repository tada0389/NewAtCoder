//#include <iostream>
//#include <string>
//#include <algorithm>
//#include <vector>
//#include <queue>
//#include <map>
//#include <set>
//#include <numeric>
//#include <iomanip>
//#include <stack>
//#include <tuple>
//#include <complex>
//#include <iterator>
//#include <cassert>
//
//#include <atcoder/modint>
//using namespace std;
//using namespace atcoder;
//
//using ll = long long;
//
//constexpr int inf = (1 << 30) - 1;
//constexpr ll infll = 1LL << 60;
//
//constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
//constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };
//
//template<class T>bool chmax(T& a, const T& b) { if (a < b) { a = b; return 1; } return 0; }
//template<class T>bool chmin(T& a, const T& b) { if (b < a) { a = b; return 1; } return 0; }
//
//template <class S,
//    S(*op)(S, S),
//    S(*e)(),
//    class F,
//    S(*mapping)(F, S),
//    F(*composition)(F, F),
//    F(*id)()>
//    struct lazy_segtree {
//    public:
//        lazy_segtree() : lazy_segtree(0) {}
//        lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
//        lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
//            auto CeilPow2 = [](int n)->int {
//                int x = 0;
//                while ((1U << x) < (unsigned int)(n)) ++x;
//                return x;
//            };
//            log = CeilPow2(_n);
//            size = 1 << log;
//            d = std::vector<S>(2 * size, e());
//            lz = std::vector<F>(size, id());
//            for (int i = 0; i < _n; i++) d[size + i] = v[i];
//            for (int i = size - 1; i >= 1; i--) {
//                update(i);
//            }
//        }
//
//        void set(int p, S x) {
//            assert(0 <= p && p < _n);
//            p += size;
//            for (int i = log; i >= 1; i--) push(p >> i);
//            d[p] = x;
//            for (int i = 1; i <= log; i++) update(p >> i);
//        }
//
//        S get(int p) {
//            assert(0 <= p && p < _n);
//            p += size;
//            for (int i = log; i >= 1; i--) push(p >> i);
//            return d[p];
//        }
//
//        S prod(int l, int r) {
//            assert(0 <= l && l <= r && r <= _n);
//            if (l == r) return e();
//
//            l += size;
//            r += size;
//
//            for (int i = log; i >= 1; i--) {
//                if (((l >> i) << i) != l) push(l >> i);
//                if (((r >> i) << i) != r) push(r >> i);
//            }
//
//            S sml = e(), smr = e();
//            while (l < r) {
//                if (l & 1) sml = op(sml, d[l++]);
//                if (r & 1) smr = op(d[--r], smr);
//                l >>= 1;
//                r >>= 1;
//            }
//
//            return op(sml, smr);
//        }
//
//        S all_prod() { return d[1]; }
//
//        void apply(int p, F f) {
//            assert(0 <= p && p < _n);
//            p += size;
//            for (int i = log; i >= 1; i--) push(p >> i);
//            d[p] = mapping(f, d[p]);
//            for (int i = 1; i <= log; i++) update(p >> i);
//        }
//        void apply(int l, int r, F f) {
//            assert(0 <= l && l <= r && r <= _n);
//            if (l == r) return;
//
//            l += size;
//            r += size;
//
//            for (int i = log; i >= 1; i--) {
//                if (((l >> i) << i) != l) push(l >> i);
//                if (((r >> i) << i) != r) push((r - 1) >> i);
//            }
//
//            {
//                int l2 = l, r2 = r;
//                while (l < r) {
//                    if (l & 1) all_apply(l++, f);
//                    if (r & 1) all_apply(--r, f);
//                    l >>= 1;
//                    r >>= 1;
//                }
//                l = l2;
//                r = r2;
//            }
//
//            for (int i = 1; i <= log; i++) {
//                if (((l >> i) << i) != l) update(l >> i);
//                if (((r >> i) << i) != r) update((r - 1) >> i);
//            }
//        }
//
//        template <bool (*g)(S)> int max_right(int l) {
//            return max_right(l, [](S x) { return g(x); });
//        }
//        template <class G> int max_right(int l, G g) {
//            assert(0 <= l && l <= _n);
//            assert(g(e()));
//            if (l == _n) return _n;
//            l += size;
//            for (int i = log; i >= 1; i--) push(l >> i);
//            S sm = e();
//            do {
//                while (l % 2 == 0) l >>= 1;
//                if (!g(op(sm, d[l]))) {
//                    while (l < size) {
//                        push(l);
//                        l = (2 * l);
//                        if (g(op(sm, d[l]))) {
//                            sm = op(sm, d[l]);
//                            l++;
//                        }
//                    }
//                    return l - size;
//                }
//                sm = op(sm, d[l]);
//                l++;
//            } while ((l & -l) != l);
//            return _n;
//        }
//
//        template <bool (*g)(S)> int min_left(int r) {
//            return min_left(r, [](S x) { return g(x); });
//        }
//        template <class G> int min_left(int r, G g) {
//            assert(0 <= r && r <= _n);
//            assert(g(e()));
//            if (r == 0) return 0;
//            r += size;
//            for (int i = log; i >= 1; i--) push((r - 1) >> i);
//            S sm = e();
//            do {
//                r--;
//                while (r > 1 && (r % 2)) r >>= 1;
//                if (!g(op(d[r], sm))) {
//                    while (r < size) {
//                        push(r);
//                        r = (2 * r + 1);
//                        if (g(op(d[r], sm))) {
//                            sm = op(d[r], sm);
//                            r--;
//                        }
//                    }
//                    return r + 1 - size;
//                }
//                sm = op(d[r], sm);
//            } while ((r & -r) != r);
//            return 0;
//        }
//
//    private:
//        int _n, size, log;
//        std::vector<S> d;
//        std::vector<F> lz;
//
//        void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
//        void all_apply(int k, F f) {
//            d[k] = mapping(f, d[k]);
//            if (k < size) lz[k] = composition(f, lz[k]);
//        }
//        void push(int k) {
//            all_apply(2 * k, lz[k]);
//            all_apply(2 * k + 1, lz[k]);
//            lz[k] = id();
//        }
//};
//
////constexpr int mod = 998244353;
//
//using mint = modint998244353;
//
//struct S {
//    mint a;
//    int size;
//};
//
//struct F {
//    mint a, b;
//};
//
//// ƒ‚ƒmƒCƒh‚Ì‡¬
//S op(S l, S r) { return S{ l.a + r.a, l.size + r.size }; }
//
//// ’PˆÊŒ³
//S e() { return S{ 0, 0 }; }
//
//// F(x) ‚ð•Ô‚·
//S mapping(F l, S r) { return S{ r.a * l.a + r.size * l.b, r.size }; }
//
//// F(F(x)) ‚ÉŠY“–‚·‚é‚â‚Â F(x)‚Ì‡¬
//F composition(F l, F r) { return F{ r.a * l.a, r.b * l.a + l.b }; }
//
//F id() { return F{ 1, 0 }; }
//
//int main() {
//
//    int n, q;
//    cin >> n >> q;
//    vector<S> a(n);
//    for (int i = 0; i < n; ++i) {
//        int x;
//        cin >> x;
//        a[i] = S{ x, 1 };
//    }
//
//    lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
//
//    vector<ll> ans;
//
//    for (int i = 0; i < q; ++i) {
//        //cout << "Contents" << endl;
//        //for (int j = 0; j < n; ++j) {
//        //    cout << seg.get(j).a << " ";
//        //}
//        //cout << endl;
//        int t;
//        cin >> t;
//        if (t == 0) {
//            int l, r, b, c;
//            cin >> l >> r >> b >> c;
//            seg.apply(l, r, F{ b, c });
//        }
//        else {
//            int l, r;
//            cin >> l >> r;
//            ans.emplace_back(seg.prod(l, r).a.val());
//        }
//    }
//
//    for (auto res : ans) cout << res << endl;
//
//    return 0;
//}