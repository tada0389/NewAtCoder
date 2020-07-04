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

#define Rep(i,a,b) for(ll i = a; i < b; ++i)
#define rep(i,b) Rep(i,0,b)
#define allof(a) (a).begin(), (a).end()

#define Yes(q) ((q) ? "Yes" : "No")
#define YES(q) ((q) ? "YES" : "NO")
#define Possible(q) ((q) ? "Possible" : "Impossible")
#define POSSIBLE(q) ((q) ? "POSSIBLE" : "IMPOSSIBLE")

using ll = long long;

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

    // 標準入出力
    struct inp {
        std::size_t sz;
        inp(std::size_t _sz = 1) : sz(_sz) {}
        template <typename T> operator T () const { T a; std::cin >> a; return a; }
        template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
        template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
    };

    inp inp1; // input one

    void WarshallFloyd(vector<vector<ll>>& dist) {
        size_t n = dist.size();
        rep(k, n) {
            rep(i, n) {
                rep(j, n) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
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

    using Graph = vector<Edge>;

    vector<vector<ll>> WarshalFloyd(Graph& G, size_t n) {

        vector<vector<ll>> dist(n, vector<ll>(n, infll));

        for (int i = 0; i < n; ++i) dist[i][i] = 0LL;

        for (const auto& edge : G) {
            dist[edge.from][edge.to] = edge.cost;
        }

        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        return dist;
    }
}

int main() {

    ll n, m, l;
    cin >> n >> m >> l;
    vector<ll> a(m), b(m), c(m);
    rep(i, m) {
        cin >> a[i] >> b[i] >> c[i];
    }
    int q = inp1;
    vector<ll> s(q), t(q);
    rep(i, q) cin >> s[i] >> t[i];

    // c > l の道のりはないものとカウントしていい

    // 隣り合う辺でコストの和が l 以下のは統合していい
    // 代わりにすべての辺のコストを lにする

    vector<vector<ll>> dist(n, vector<ll>(n, infll));

    rep(i, m) {
        dist[a[i] - 1][b[i] - 1] = c[i];
        dist[b[i] - 1][a[i] - 1] = c[i];
    }

    // O(n^3)
    WarshallFloyd(dist);

    vector<vector<ll>> dist_2(n, vector<ll>(n, infll));

    rep(i, n) {
        rep(j, n) {
            if (dist[i][j] <= l) {
                dist_2[i][j] = 1;
            }
        }
    }

    WarshallFloyd(dist_2);

    rep(i, q) {
        ll ans = dist_2[s[i] - 1][t[i] - 1];

        if (ans == infll) ans = 0;
        Cout(ans - 1);
    }

    return 0;
}

// https://atcoder.jp/contests/agc039/tasks/agc039_b
int main() {

    int n = inp1;
    vector<string> s = inp(n);
    Graph G;

    rep(i, n) {
        rep(j, s[i].size()) {
            if (s[i][j] == '1') G.emplace_back(Edge(i, j, 1)), G.emplace_back(Edge(j, i, 1));
        }
    }

    auto dist = WarshalFloyd(G, n);

    int ans = -1;

    rep(i, n) {
        bool can = true;

        vector<int> group(n, -1);
        rep(j, n) {
            group[j] = dist[i][j];
        }

        for (auto edge : G) {
            int dif = group[edge.from] - group[edge.to];
            if (dif != 1 && dif != -1) {
                can = false;
                break;
            }
        }

        if (can) chmax(ans, *max_element(allof(group)) + 1);
    }

    Cout(ans);

    return 0;
}
