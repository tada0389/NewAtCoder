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
    template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
    template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

    void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; ++i) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }

    // 標準入出力
    struct Read {
        std::size_t szi, szj;
        Read(std::size_t _szi = 1, std::size_t _szj = 1) : szi(_szi), szj(_szj) {}
        template <typename T> operator T () const { T a; std::cin >> a; return a; }
        template <typename T> operator std::vector<T>() const { std::vector<T> a(szi); for (std::size_t i = 0; i < szi; ++i) std::cin >> a[i]; return a; }
        template <typename T> operator std::vector<std::vector<T>>() const {
            std::vector<std::vector<T>> a(szi, std::vector<T>(szj));
            for (std::size_t i = 0; i < szi; ++i) for (std::size_t j = 0; j < szj; ++j) cin >> a[i][j]; return a;
        }
    };
    Read inp1;

    // 蟻本から自分なりに改良
    // 計算量 E A(n)

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

    using Graph = std::vector<Edge>;

    struct UnionFind {
    private:
        const int n;
        int __size;
        std::vector<int> uf;
    public:
        // 初期化 UnionFind uni(n) のように宣言すれば良い
        UnionFind(int _n) : n(_n), __size(_n), uf(_n, -1) {}
        // find (木の根を求める)
        int find(int x) { return (uf[x] < 0) ? x : uf[x] = find(uf[x]); }
        // x と y が同じ集合に属するかどうか
        bool same(int x, int y) { return find(x) == find(y); }
        // x が属する集合の要素数
        int size(int x) { return -uf[find(x)]; }
        // 集合はいくつあるか
        int size() { return __size; }
        // x と y の属する集合を併合
        bool unite(int x, int y) {
            x = find(x); y = find(y);
            if (x == y) return false;
            __size--;
            if (uf[y] < uf[x]) swap(x, y);
            uf[x] += uf[y]; uf[y] = x;
            return true;
        }
    };

    // 最小全域木を求める firstは最小コスト secondは必要な辺の数
    std::pair<ll, int> Kruskal(Graph& G, const int n) {
        // 辺のコストが小さい順に並べる
        std::sort(G.begin(), G.end());
        UnionFind uni(n);

        std::pair<ll, int> res;
        for (int i = 0, sz = G.size(); i < sz; ++i) {
            Edge e = G[i];
            // すでに同じグループなら繋げない
            if (uni.same(e.from, e.to)) continue;
            uni.unite(e.from, e.to);
            res.first += e.cost;
            ++res.second;
        }

        return res;
    }
}

int main() {

    int n = inp1;
    Graph G;

    vector<tuple<int, int, int>> points(n);
    rep(i, n) {
        int x, y;
        cin >> x >> y;
        points[i] = make_tuple(x, y, i);
    }

    // |x2 - x1| の辺と |y2 - y1| の辺を考える
    // |x3 - x1| の辺は |x3 - x2| + |x2 - x1| なので必要ない

    sort(allof(points), [](const auto& lhs, const auto& rhs) {
        return get<0>(lhs) < get<0>(rhs);
        });

    rep(i, n - 1) {
        //auto [x1, y1, from] = points[i];
        int x1, y1, from;
        tie(x1, y1, from) = points[i];
        int x2, y2, to;
        tie(x2, y2, to) = points[i + 1];
        int dist = min(abs(x2 - x1), abs(y2 - y1));
        G.emplace_back(Edge(from, to, dist));
    }

    sort(allof(points), [](const auto& lhs, const auto& rhs) {
        return get<1>(lhs) < get<1>(rhs);
        });

    rep(i, n - 1) {
        int x1, y1, from;
        tie(x1, y1, from) = points[i];
        int x2, y2, to;
        tie(x2, y2, to) = points[i + 1];
        int dist = min(abs(x2 - x1), abs(y2 - y1));
        G.emplace_back(Edge(from, to, dist));
    }

    auto ans = Kruskal(G, n);

    Cout(ans.first);

    return 0;
}
