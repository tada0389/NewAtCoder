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
#include <stdio.h>
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

using ll =  long long;

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
	struct inp {
		size_t sz;
		inp(size_t _sz = 1) : sz(_sz) {}
		template <typename T> operator T () const { T a; std::cin >> a; return a; }
		template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
		template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
	};

	inp inp1; // input one

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
			data = std::vector<T>(2 * n - 1, def);
		}

		// 場所i(0-indexed)の値をxで更新
		void change(int i, T x) {
			i += n - 1;
			data[i] = update(data[i], x);
			while (i > 0) {
				i = (i - 1) / 2;
				data[i] = operation(data[i * 2 + 1], data[i * 2 + 2]);
			}
		}

		// [a, b)の区間クエリを実行
		T query(int a, int b) {
			return _query(a, b, 0, 0, n);
		}

		// 添字でアクセス
		T operator[](int i) {
			return data[i + n - 1];
		}
	private:
		int n;                       // 葉の数
		std::vector<T> data;              // データを格納するvector
		T def;                       // 初期値かつ単位元
		std::function<T(T, T)> operation; // 区間クエリで使う処理
		std::function<T(T, T)> update;    // 点更新で使う処理

		// 区間[a,b)の総和。ノードk=[l,r)に着目している。
		T _query(int a, int b, int k, int l, int r) {
			if (r <= a || b <= l) return def; // 交差しない
			if (a <= l && r <= b)
				return data[k]; // a,l,r,bの順で完全に含まれる
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

	SegmentTree<int> seg(n, 0, [](int a, int b)->int {return a + b; }, [](int a, int b)->int {return a + b; });

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