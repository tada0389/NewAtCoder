#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
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
// 0~3までは右下左上 4~7までは斜め
constexpr int dx[] = { 1, 0, -1, 0, 1, -1 };
constexpr int dy[] = { 0, 1, 0, -1, 1, 1 };

namespace {
    template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
    template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

    void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; ++i) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }

    // 標準入出力
    struct inp {
        std::size_t szi, szj;
        inp(std::size_t _szi = 1, std::size_t _szj = 1) : szi(_szi), szj(_szj) {}
        template <typename T> operator T () const { T a; std::cin >> a; return a; }
        template <typename T> operator std::vector<T>() const { std::vector<T> a(szi); for (std::size_t i = 0; i < szi; ++i) std::cin >> a[i]; return a; }
        template <typename T> operator std::vector<std::vector<T>>() const {
            std::vector<std::vector<T>> a(szi, std::vector<T>(szj));
            for (std::size_t i = 0; i < szi; ++i) for (std::size_t j = 0; j < szj; ++j) cin >> a[i][j]; return a;
        }
    };
    inp inp1;

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

    // LCA ２つのノードを渡して最小共通祖先を求める
    // 根付き木構造で使える
    class LCA {
    public:
        LCA(const Graph& G, int root = 0) {
            Init(G, root);
        }

        // ２つの頂点の最小共通祖先を求める
        int GetAncestor(int u, int v) {
            if (dist[u] < dist[v]) swap(u, v);
            int k = parent.size();
            // LCAまでの距離を同じにする
            for (int i = 0; i < k; ++i) {
                if ((dist[u] - dist[v]) >> i & 1) u = parent[i][u];
            }

            // 二分探索でLCAを求める
            if (u == v) return u;
            for (int i = k - 1; i >= 0; --i) {
                if (parent[i][u] != parent[i][v]) {
                    u = parent[i][u];
                    v = parent[i][v];
                }
            }
            return parent[0][u];
        }

        // ２点間の距離を求める
        int GetDist(int u, int v) {
            return dist[u] + dist[v] - 2 * dist[GetAncestor(u, v)];
        }

        // 二点間のパス上に指定した頂点がある
        bool IsOnPath(int u, int v, int a) {
            return GetDist(u, a) + GetDist(a, v) == GetDist(u, v);
        }

    private:
        // 初期化
        void Init(const Graph& G, int root = 0) {
            int v = G.size();
            int k = 1;
            while ((1 << k) < v) ++k;
            parent.assign(k, vector<int>(v, -1));
            dist.assign(v, -1);
            dfs(G, root, -1, 0);
            for (int i = 0; i + 1 < k; ++i) {
                for (int j = 0; j < v; ++j) {
                    if (parent[i][j] < 0) parent[i + 1][j] = -1; // 親の場合
                    else parent[i + 1][j] = parent[i][parent[i][j]]; // ダブリンぐ
                }
            }
        }

        // 根からの距離と一つ先の頂点を求める
        void dfs(const Graph& G, int v, int p, int d) {
            parent[0][v] = p;
            dist[v] = d;
            for (auto e : G[v]) {
                if (e.to != p) dfs(G, e.to, v, d + 1);
            }
        }

        vector<vector<int>> parent; // parent[k][u] := uの2^k先の親
        vector<int> dist; // rootからの距離


    };
}


// https://atcoder.jp/contests/past201912-open/tasks/past201912_k
int main() {

    int n = inp1;
    vector<int> p = inp(n);

    Graph G(n);
    int root = 0;
    rep(i, n) {
        if (p[i] == -1) root = i;
        else G[p[i] - 1].emplace_back(Edge(i));
    }
    LCA lca(G, root);

    int q = inp1;

    // 木構造

    vector<string> ans(q);

    rep(i, q) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        bool ok = false;
        int root = lca.GetAncestor(a, b);
        if (root == b) ok = true;

        ans[i] = Yes(ok);
    }

    for (auto r : ans) Cout(r);

    return 0;
}
