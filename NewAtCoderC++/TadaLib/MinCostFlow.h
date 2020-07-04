//#include <iostream>
//#include <string>
//#include <algorithm>
//#include <vector>
//#include <queue>
//#include <map>
//#include <unordered_map>
//#include <set>
//#include <unordered_set>
//#include <cmath>
//#include <numeric>
//#include <iomanip>
//#include <stack>
//#include <complex>
//#include <functional>
//#include <tuple>
//
//using namespace std;
//
//#define Rep(i,a,b) for(ll i = a; i < b; ++i)
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
//constexpr int inf = 1e9 + 7;
//constexpr ll infll = 1ll << 60ll;
//constexpr ll mod = 998244353;
//// 0~3までは右下左上 4~7までは斜め
//constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
//constexpr int dy[] = { 0, 1, 0, -1, -1, 1, 1, -1 };
//
//namespace {
//    template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
//    template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }
//
//    void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
//    template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
//    template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; ++i) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }
//
//    // 標準入出力
//    struct inp {
//        std::size_t szi, szj;
//        inp(std::size_t _szi = 1, std::size_t _szj = 1) : szi(_szi), szj(_szj) {}
//        template <typename T> operator T () const { T a; std::cin >> a; return a; }
//        template <typename T> operator std::vector<T>() const { std::vector<T> a(szi); for (std::size_t i = 0; i < szi; ++i) std::cin >> a[i]; return a; }
//        template <typename T> operator std::vector<std::vector<T>>() const {
//            std::vector<std::vector<T>> a(szi, std::vector<T>(szj));
//            for (std::size_t i = 0; i < szi; ++i) for (std::size_t j = 0; j < szj; ++j) cin >> a[i][j]; return a;
//        }
//    };
//    inp inp1;
//
//	class MinCostFlow {
//	public:
//		struct edge { ll to, capacity; double cost; ll reve; };
//		static const int MV = 5000;
//		vector<edge> E[MV];
//		double dist[MV];
//		ll prev_v[MV], prev_e[MV], NV;
//
//		void init(int NV) { this->NV = NV; for (int i = 0; i < MV; i++) E[i].clear(); }
//		void add_edge(int x, int y, ll cap, double cost) {
//			E[x].push_back((edge) { y, cap, cost, E[y].size() });
//			E[y].push_back((edge) { x, 0, -cost, E[x].size() - 1 }); /* rev edge */
//		}
//
//		double mincost(int from, int to, ll flow) {
//			double res = 0;
//			int i, v;
//			ZERO(prev_v); ZERO(prev_e);
//			while (flow > 0) {
//				fill(dist, dist + NV, 1e10);
//				dist[from] = 0;
//				bool up = true;
//				while (up) {
//					up = false;
//					FOR(v, NV) {
//						if (dist[v] == 1e10) continue;
//						FOR(i, E[v].size()) {
//							edge& e = E[v][i];
//							if (e.capacity > 0 && dist[e.to] > dist[v] + e.cost) {
//								dist[e.to] = dist[v] + e.cost;
//								prev_v[e.to] = v;
//								prev_e[e.to] = i;
//								up = true;
//							}
//						}
//					}
//				}
//
//				if (dist[to] == 1e10) return -1;
//				ll lc = flow;
//				for (v = to; v != from; v = prev_v[v]) lc = min(lc, E[prev_v[v]][prev_e[v]].capacity);
//				flow -= lc;
//				res += lc * dist[to];
//				for (v = to; v != from; v = prev_v[v]) {
//					edge& e = E[prev_v[v]][prev_e[v]];
//					e.capacity -= lc;
//					E[v][e.reve].capacity += lc;
//				}
//			}
//			return res;
//		}
//	};
//}
//
//int main() {
//
//    int n = inp1;
//    vector<pair<double, double>> xy(n);
//    rep(i, n) cin >> xy[i].first >> xy[i].second;
//
//    // 真ん中ならペアにならなくてもよい
//
//    double ans = 100000000000.0;
//
//    rep(bit, (1LL << n)) {
//        double tmp = 0.0;
//        vector<int> selected;
//        rep(i, n) {
//            if ((bit << i) & 1) selected.emplace_back(i), tmp += xy[i].first;
//        }
//
//        if (selected.size() % 2 == 1) continue;
//
//        // ペアを全探索
//
//    }
//
//    return 0;
//}
