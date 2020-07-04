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
    struct inp {
        size_t sz;
        inp(size_t _sz = 1) : sz(_sz) {}
        template <typename T> operator T () const { T a; std::cin >> a; return a; }
        template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
        template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
    };

    inp inp1; // input one

    // 二分探索を行うライブラリ
    // @author tada
    // T は返り値の型
    template<typename T>
    T BinarySearch(T left, T right, std::function<bool(T)> Check) {
        while (right - left > 1) {
            T mid = (right + left) / 2;
            if (Check(mid)) left = mid; // 右を探す
            else right = mid;                       // 左を探す
        }
        // mid = left, mid = right - 1 となっている
        return left;
    }
}


// https://atcoder.jp/contests/exawizards2019/tasks/exawizards2019_c
//int main() {
//
//	int n, q;
//	string s;
//	cin >> n >> q >> s;
//	vector<char> t(q), d(q);
//	rep(i, q) cin >> t[i] >> d[i];
//
//	int left_drop = BinarySearch<int>(0, n, [&](int mid)->bool {
//		// midが左にドロップするかどうか
//		int pos = mid;
//		bool drop = false;
//		rep(i, q) {
//			if (s[pos] != t[i]) continue;
//			// 移動する番
//			if (d[i] == 'L') --pos;
//			else ++pos;
//
//			if (pos < 0) {
//				drop = true;
//				break;
//			}
//			if (pos >= n) {
//				break;
//			}
//		}
//		return drop;
//		});
//
//	int right_drop = BinarySearch<int>(0, n, [&](int mid)->bool {
//		// midが右にドロップするかどうか
//		int pos = mid;
//		bool drop = false;
//		rep(i, q) {
//			if (s[pos] != t[i]) continue;
//			// 移動する番
//			if (d[i] == 'L') --pos;
//			else ++pos;
//
//			if (pos < 0) {
//				//drop = true;
//				break;
//			}
//			if (pos >= n) {
//				drop = true;
//				break;
//			}
//		}
//		return !drop;
//		}) + 1;
//
//	int ans = right_drop - left_drop - 1;
//	Cout(ans);
//
//	return 0;
//}