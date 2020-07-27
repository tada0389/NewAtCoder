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
#include <tuple>

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

    void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; i++) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }

    void CCout(long long x, const char* end = "\n") { std::cerr << x << end; }
    template <typename T> void CCout(const T& x, const char* end = "\n") { std::cerr << x << end; }
    template <typename T> void CCout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; i++) { std::cerr << x[i] << (i == sz - 1 ? end : sep); } }

    // 標準入出力
    struct Read {
        std::size_t sz;
        Read(std::size_t _sz = 1) : sz(_sz) {}
        template <typename T> operator T () const { T a; std::cin >> a; return a; }
        template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
        template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
    };

    Read inp1; // input one

    // ベルマンフォードのライブラリ
    template<typename T>
    vector<T> bellman_ford(vector<vector<pair<int, T>>> g, int s, int trial = 1) {
        int n = (int)g.size();
        const auto inf = numeric_limits<T>::max();
        vector<T> dist(n, inf);
        dist[s] = 0;
        for (int i = 0; i < trial * (n - 1); ++i) {
            for (int u = 0; u < n; ++u) {
                for (const auto& e : g[u]) {
                    if (dist[u] == inf) continue;
                    dist[e.first] = min(dist[e.first], dist[u] + e.second);
                }
            }
        }

        return dist;
    }

    struct Edge {
        ll from; // 移動前のノード
        ll to; // 移動先のノード
        ll cost; // 辺のコスト
        ll hoge; // 任意変更 いらないかも

        Edge() = default;
        Edge(ll _to) : from(-1), to(_to), cost(1), hoge(-1) {};
        Edge(ll _to, ll _cost) : from(-1), to(_to), cost(_cost), hoge(-1) {};
        Edge(ll _from, ll _to, ll _cost) : from(_from), to(_to), cost(_cost), hoge(-1) {};
        Edge(ll _from, ll _to, ll _cost, ll _hoge) : from(_from), to(_to), cost(_cost), hoge(_hoge) {};
        bool operator< (const Edge& rhs) const {
            return cost < rhs.cost;
        }
        bool operator> (const Edge& rhs) const {
            return cost > rhs.cost;
        }
        bool operator==(const Edge& rhs) const {
            if (from != rhs.from) return false;
            if (to != rhs.to) return false;
            if (cost != rhs.cost) return false;
            if (hoge != rhs.hoge) return false;
            return true;
        }
        bool operator!=(const Edge& rhs) const {
            if (from != rhs.from) return true;
            if (to != rhs.to) return true;
            if (cost != rhs.cost) return true;
            if (hoge != rhs.hoge) return true;
            return false;
        }
    };

    using Graph = vector<vector<Edge>>;

    // ベルマンフォードのライブラリ
    // trialは試行回数 trial=1のときとtrial2のときの最短距離が異なるなら閉路になっている
    // 計算量 O(|V||E|)
    template<typename T>
    vector<T> bellman_ford(int s, Graph& G, int trial = 1) {
        int n = G.size();
        const auto inf = numeric_limits<T>::max();
        vector<T> dist(n, inf);
        dist[s] = 0;
        for (int i = 0; i < trial * (n - 1); ++i) {
            for (int u = 0; u < n; ++u) {
                for (const auto& e : G[u]) {
                    if (dist[u] == inf) continue;
                    dist[e.to] = min(dist[e.to], dist[u] + e.cost);
                }
            }
        }

        return dist;
    }
}

int main() {

    int n, m;
    cin >> n >> m;
    Graph G(n);
    rep(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        G[a].emplace_back(Edge(b, -c));
    }

    auto dist1 = bellman_ford<ll>(0, G, 1);
    auto dist2 = bellman_ford<ll>(0, G, 2);

    if (dist1[n - 1] != dist2[n - 1]) Cout("inf");
    else Cout(-dist1[n - 1]);

    return 0;
}


int main() {

    int n, m, p;
    cin >> n >> m >> p;
    vector<int> a(m), b(m), c(m);
    vector<vector<pair<int, ll>>> g(n);
    rep(i, m) {
        cin >> a[i] >> b[i] >> c[i];
        --a[i], --b[i];
        g[a[i]].push_back({ b[i], -c[i] + p });
    }

    vector<ll> dist1 = bellman_ford<ll>(g, 0, 1);
    vector<ll> dist2 = bellman_ford<ll>(g, 0, 2);

    if (dist1[n - 1] != dist2[n - 1]) Cout(-1);
    else Cout(max(0LL, -dist1[n - 1]));

    return 0;
}
