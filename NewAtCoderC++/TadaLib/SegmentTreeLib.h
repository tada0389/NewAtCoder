#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <list>
#include <numeric>
#include <stack>
#include <iomanip>
#include <random>
#include <complex>
#include <functional>

using namespace std;

#define Rep(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,b) Rep(i,0,b)
#define allof(a) (a).begin(), (a).end()

#define Yes(q) ((q) ? "Yes" : "No")
#define YES(q) ((q) ? "YES" : "NO")
#define Possible(q) ((q) ? "Possible" : "Impossible")
#define POSSIBLE(q) ((q) ? "POSSIBLE" : "IMPOSSIBLE")

using ll = long long;

using pint = std::pair<int, int>;
using pll = std::pair<ll, ll>;


constexpr int inf = 1e9 + 7;
constexpr ll infll = 1ll << 60ll;
constexpr ll mod = 1e9 + 7;
// 0~3までは右左下上 4~7までは斜め
constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };

namespace {
    template<typename T> void chmax(T& a, T b) { a = std::max(a, b); }
    template<typename T> void chmin(T& a, T b) { a = std::min(a, b); }
    template<typename T> void chadd(T& a, T b) { a = a + b; }
    template<typename T> T gcd(T a, T b) { if (a < b) std::swap(a, b); while (b) std::swap(a %= b, b); return a; }
    template<typename T> T lcm(const T a, const T b) { return a / gcd(a, b) * b; }

    template <typename T> void Cout(T& x, char end = '\n') { std::cout << x << end; }
    template <typename T> void Cout(std::vector<T>& x, char sep = ' ', char end = '\n') { for (std::size_t i = 0, sz = x.size(); i < sz; i++) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }


    // 標準入出力
    struct Read {
        size_t sz;
        Read(size_t _sz = 1) : sz(_sz) {}
        template <typename T> operator T () const { T a; std::cin >> a; return a; }
        template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
        template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
    };

    Read inp1; // input one

    // セグメントツリーのライブラリ
    template<typename T>
    class SegmentTree {
    public:
        // _n:必要サイズ, _def:初期値かつ単位元, _operation:クエリ関数,
        // _update:更新関数
        SegmentTree(size_t _n, T _def, std::function<T(T, T)> _operation,
            std::function<T(T, T)> _update)
            : def(_def), operation(_operation), update(_update) {
            n = 1;
            while (n < _n) {
                n *= 2;
            }
            node = std::vector<T>(2 * n - 1, def);
        }

        // 場所i(0-indexed)の値をxで更新
        void change(int i, T x) {
            i += n - 1;
            node[i] = update(node[i], x);
            while (i > 0) {
                i = (i - 1) / 2;
                node[i] = operation(node[i * 2 + 1], node[i * 2 + 2]);
            }
        }

        // [a, b)の区間クエリを実行
        T query(int a, int b) {
            return _query(a, b, 0, 0, n);
        }

        // 添字でアクセス
        T operator[](int i) {
            return node[i + n - 1];
        }

        int n;                       // 葉の数
        std::vector<T> node;              // データを格納するvector
    private:
        T def;                       // 初期値かつ単位元
        std::function<T(T, T)> operation; // 区間クエリで使う処理
        std::function<T(T, T)> update;    // 点更新で使う処理

        // 区間[a,b)の総和。ノードk=[l,r)に着目している。
        T _query(int a, int b, int k, int l, int r) {
            if (r <= a || b <= l) return def; // 交差しない
            if (a <= l && r <= b)
                return node[k]; // a,l,r,bの順で完全に含まれる
            else {
                T c1 = _query(a, b, 2 * k + 1, l, (l + r) / 2); // 左の子
                T c2 = _query(a, b, 2 * k + 2, (l + r) / 2, r); // 右の子
                return operation(c1, c2);
            }
        }
    };
}


// https://atcoder.jp/contests/exawizards2019/tasks/exawizards2019_c
int main() {

    int n, q;
    std::cin >> n >> q;
    std::vector<int> com(q), x(q), y(q);
    rep(i, q) std::cin >> com[i] >> x[i] >> y[i];

    //SegmentTree<int> seg(n, inf,[](int a, int b)->int {return std::min(a, b); }, [](int a, int b)->int {return b; });

    //for (int i = 0; i < q; ++i) {
    //	if(com[i] == 0) seg.change(x[i], y[i]);
    //	else std::cout << seg.query(x[i], y[i] + 1) << std::endl;
    //}

    auto update = [](int a, int b) {return a + b; };
    auto operation = [](int a, int b) {return a + b; };
    SegmentTree<int> seg(n, 0, operation, update);

    for (int i = 0; i < q; ++i) {
        if (com[i] == 0) seg.change(x[i] - 1, y[i]);
        else std::cout << seg.query(x[i] - 1, y[i]) << std::endl;
    }
}

// https://atcoder.jp/contests/abc157/tasks/abc157_e
//int main() {
//
//	int n = inp1;
//	string s = inp1;
//	int q = inp1;
//
//	auto f = [](int a, int b)->int {
//		return a + b;
//	};
//	auto g = [](int a, int b)->int {
//		return a + b;
//	};
//
//	// 絶対セグ木
//	vector<SegmentTree<int>> segs(26, SegmentTree<int>(n, 0,
//		//[](int a, int b)->int {return a + b; }, // update 
//		//[](int a, int b)->int {return a + b; } // return
//		f,
//		g
//		));
//
//	// 初期化
//	rep(i, s.size()) {
//		segs[(s[i] - 'a')].change(i, 1);
//	}
//
//	// 文字の種類
//	rep(query, q) {
//		int b = inp1;
//		if (b == 1) { // 文字を変更
//			int i = inp1;
//			char c = inp1;
//			segs[(s[i - 1] - 'a')].change(i - 1, -1);
//			segs[(c - 'a')].change(i - 1, 1);
//			s[i - 1] = c;
//		}
//		else { // 解を返す
//			int l, r;
//			cin >> l >> r;
//			int res = 0;
//			rep(i, 26) {
//				if (segs[i].query(l - 1, r) > 0) ++res;
//			}
//			Cout(res);
//		}
//	}
//
//	return 0;
//}

//// https://codeforces.com/gym/102091/attachments/download/8314/20182019-acmicpc-asia-nakhon-pathom-regional-contest-en.pdf
//int main() {
//
//    int q;
//    scanf_s("%d", &q);
//
//    rep(t, q) {
//        int n;
//        scanf_s("%d", &n);
//
//        vector<tuple<int, int, int>> events;
//
//        vector<int> values;
//
//        rep(i, n) {
//            int op = inp1;
//            if (op == 1) {
//                int a, b, c;
//                scanf_s("%d %d %d", &a, &b, &c);
//                events.emplace_back(a, -1, b);
//                events.emplace_back(c, 1, b);
//                values.emplace_back(b);
//            }
//            else {
//                int a, b;
//                scanf_s("%d %d", &a, &b);
//                events.emplace_back(a, 0, b);
//            }
//        }
//
//        sort(allof(values));
//        values.erase(unique(allof(values)), values.end());
//
//        SegmentTree<int> seg(values.size(), 0, [](int a, int b)->int {return a + b; }, [](int a, int b)->int {return a + b; });
//
//        sort(allof(events));
//
//        vector<int> ans;
//
//        for (auto e : events) {
//            int cur_time, op, val;
//            tie(cur_time, op, val) = e;
//
//            if (op == -1) {
//                // 追加
//                int i = lower_bound(allof(values), val) - values.begin();
//                seg.change(i, 1);
//            }
//            else if (op == 1) {
//                // 消去
//                int i = lower_bound(allof(values), val) - values.begin();
//                seg.change(i, -1);
//            }
//            else {
//                // 取得
//                if (seg.node[0] < val) {
//                    ans.emplace_back(-1);
//                    continue;
//                }
//                int i = 0;
//                int s = 0;
//                while (i < seg.n - 1) { // 最下段ではない条件
//                    int c1 = 2 * i + 1, c2 = 2 * i + 2;
//                    if (s + seg.node[c1] >= val) {
//                        i = c1;
//                    }
//                    else {
//                        i = c2;
//                        s += seg.node[c1];
//                    }
//                }
//                int res = i - (seg.n - 1); // セグ木の最下段の配列の添え字に変換
//                ans.emplace_back(values[res]);
//            }
//        }
//
//        printf_s("Case %d:\n", (t + 1));
//        rep(i, ans.size()) printf_s("%d\n", ans[i]);
//    }
//
//    return 0;
//}

// https://atcoder.jp/contests/arc035/tasks/arc035_d
int main() {

    int n;
    cin >> n;
    vector<int> p(n), q(n);
    rep(i, n) cin >> p[i] >> q[i];
    int query = inp1;

    auto update = [](double a, double b) {return b; };
    auto operation = [](double a, double b) {return a + b; };
    SegmentTree<double> seg(n - 1, 0, operation, update);

    // a * b * c とめっちゃでかくなる
    // log取る HCPCで履修済み

    const int kMax = 2000020;
    vector<double> facts(kMax);
    facts[1] = log(1);
    Rep(i, 2, kMax) facts[i] = facts[i - 1] + log(i);

    rep(i, n - 1) {
        int dx = abs(p[i + 1] - p[i]);
        int dy = abs(q[i + 1] - q[i]);
        double v = facts[dx + dy] - facts[dx] - facts[dy];
        seg.change(i, v);
    }

    vector<string> ans;
    rep(i, query) {
        int t = inp1;
        if (t == 1) {
            int k, a, b;
            cin >> k >> a >> b;
            --k;
            p[k] = a;
            q[k] = b;
            if (k != n - 1) {
                int dx = abs(p[k + 1] - p[k]);
                int dy = abs(q[k + 1] - q[k]);
                double v = facts[dx + dy] - facts[dx] - facts[dy];
                seg.change(k, v);
            }
            if (k != 0) {
                int dx = abs(p[k] - p[k - 1]);
                int dy = abs(q[k] - q[k]);
                double v = facts[dx + dy] - facts[dx] - facts[dy];
                seg.change(k - 1, v);
            }
        }
        else {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            double first = seg.query(l1 - 1, r1 - 1);
            double second = seg.query(l2 - 1, r2 - 1);
            //cout << first << " vs " << second << endl;
            if (first >= second) ans.emplace_back("FIRST");
            else ans.emplace_back("SECOND");
        }
    }

    for (auto s : ans) Cout(s);

    return 0;
}
