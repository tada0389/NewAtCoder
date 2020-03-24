//#include <iostream>
//#include <string>
//#include <algorithm>
//#include <vector>
//#include <array>
//#include <queue>
//#include <deque>
//#include <map>
//#include <set>
//#include <sstream>
//#include <cstdio>
//#include <cstring>
//#include <cmath>
//#include <list>
//#include <numeric>
//#include <stack>
//#include <iomanip>
//#include <random>
//#include <complex>
//#include <functional>
//#include <tuple>
//
//using namespace std;
//
//#define Rep(i,a,b) for(int i = a; i < b; ++i)
//#define rep(i,b) Rep(i,0,b)
//#define allof(a) (a).begin(), (a).end()
//
//#define Yes(q) ((q) ? "Yes" : "No")
//#define YES(q) ((q) ? "YES" : "NO")
//#define Possible(q) ((q) ? "Possible" : "Impossible")
//#define POSSIBLE(q) ((q) ? "POSSIBLE" : "IMPOSSIBLE")
//
//using ll = long long;
//
//using pint = std::pair<int, int>;
//using pll = std::pair<ll, ll>;
//
//
//constexpr int inf = 1e9 + 7;
//constexpr ll infll = 1ll << 60ll;
//constexpr ll mod = 1e9 + 7;
//// 0~3�܂ł͉E������ 4~7�܂ł͎΂�
//constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
//constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };
//
//namespace {
//	template<typename T> void chmax(T& a, T b) { a = std::max(a, b); }
//	template<typename T> void chmin(T& a, T b) { a = std::min(a, b); }
//	template<typename T> void chadd(T& a, T b) { a = a + b; }
//
//	void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
//	template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
//	template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; i++) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }
//
//	void CCout(long long x, const char* end = "\n") { std::cerr << x << end; }
//	template <typename T> void CCout(const T& x, const char* end = "\n") { std::cerr << x << end; }
//	template <typename T> void CCout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; i++) { std::cerr << x[i] << (i == sz - 1 ? end : sep); } }
//
//	// �W�����o��
//	struct inp {
//		std::size_t sz;
//		inp(std::size_t _sz = 1) : sz(_sz) {}
//		template <typename T> operator T () const { T a; std::cin >> a; return a; }
//		template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
//		template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
//	};
//
//	inp inp1; // input one
//}
//
//int main() {
//
//	//string l = inp1;
//
//	//// �Е���0�Ȃ�K��OK
//	//// �J��グ���Ȃ��ꍇ��OK (��������1�������Ȃ�)
//	//size_t n = l.length();
//	//// A�����B�̒l�̏ォ��k���ڂ܂Ŋm�肳���C���̎��_�ł��ł�A+B��L�ȉ��ł��邱�Ƃ��������Ă���g�̐�
//	//vector<ll> dp1(n, 0);
//	//// A�����B�̒l�̏ォ��k���ڂ܂Ŋm�肳���C���̎��_�ł��ł�A+B��L�ȉ��ł��邱�Ƃ��������Ă��Ȃ��g�̐�
//	//vector<ll> dp2(n, 0);
//
//	string s = inp1;
//	int k = inp1;
//	size_t n = s.length();
//
//	// dp[i][j][k] := �ォ��i���ڂ܂Ō��߂āC0�łȂ�����j����CN��菬�������Ƃ��m�肵�Ă���/���Ȃ� 0/1
//	vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(k + 1, vector<ll>(2, 0)));
//
//	// �ꌅ�ڂ͂��炩���ߌ��߂�
//	dp[1][0][0] = 1;
//	dp[1][1][0] = (s[0] - '0') - 1;
//	dp[1][1][1] = 1; // �����Ɠ���
//
//	Rep(i, 1, n) {
//		rep(j, k) {
//			// N��菬�������Ƃ��m�肵�Ă���
//			// ���̌���0�ȊO 9�ʂ�
//			dp[i + 1][j + 1][0] += dp[i][j][0] * 9;
//			// 0
//			dp[i + 1][j][0] += dp[i][j][0];
//
//			// �m�肵�Ă��Ȃ�
//			int d = s[i] - '0';
//			if (d == 0) {
//				dp[i + 1][j][1] += dp[i][j][1];
//			}
//			else {
//				dp[i + 1][j + 1][0] += dp[i][j][1] * (d - 1);
//				dp[i + 1][j + 1][1] += dp[i][j][1];
//			}
//		}
//		// k��������Ă�����i�߂�
//		dp[i + 1][k][0] += dp[i][k][0];
//		dp[i + 1][k][1] += dp[i][k][1];
//	}
//
//	Cout(dp[n][k][0] + dp[n][k][1]);
//
//	return 0;
//}