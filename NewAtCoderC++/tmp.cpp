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
//constexpr int inf = 1e9 + 7;
//
//
//namespace atcoder {
//    namespace internal {
//
//        template <class E> struct csr {
//            std::vector<int> start;
//            std::vector<E> elist;
//            csr(int n, const std::vector<std::pair<int, E>>& edges)
//                : start(n + 1), elist(edges.size()) {
//                for (auto e : edges) {
//                    start[e.first + 1]++;
//                }
//                for (int i = 1; i <= n; i++) {
//                    start[i] += start[i - 1];
//                }
//                auto counter = start;
//                for (auto e : edges) {
//                    elist[counter[e.first]++] = e.second;
//                }
//            }
//        };
//
//        // Reference:
//        // R. Tarjan,
//        // Depth-First Search and Linear Graph Algorithms
//        struct scc_graph {
//        public:
//            scc_graph(int n) : _n(n) {}
//
//            int num_vertices() { return _n; }
//
//            void add_edge(int from, int to) { edges.push_back({ from, {to} }); }
//
//            // @return pair of (# of scc, scc id)
//            std::pair<int, std::vector<int>> scc_ids() {
//                auto g = csr<edge>(_n, edges);
//                int now_ord = 0, group_num = 0;
//                std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
//                visited.reserve(_n);
//                auto dfs = [&](auto self, int v) -> void {
//                    low[v] = ord[v] = now_ord++;
//                    visited.push_back(v);
//                    for (int i = g.start[v]; i < g.start[v + 1]; i++) {
//                        auto to = g.elist[i].to;
//                        if (ord[to] == -1) {
//                            self(self, to);
//                            low[v] = std::min(low[v], low[to]);
//                        }
//                        else {
//                            low[v] = std::min(low[v], ord[to]);
//                        }
//                    }
//                    if (low[v] == ord[v]) {
//                        while (true) {
//                            int u = visited.back();
//                            visited.pop_back();
//                            ord[u] = _n;
//                            ids[u] = group_num;
//                            if (u == v) break;
//                        }
//                        group_num++;
//                    }
//                };
//                for (int i = 0; i < _n; i++) {
//                    if (ord[i] == -1) dfs(dfs, i);
//                }
//                for (auto& x : ids) {
//                    x = group_num - 1 - x;
//                }
//                return { group_num, ids };
//            }
//
//            std::vector<std::vector<int>> scc() {
//                auto ids = scc_ids();
//                int group_num = ids.first;
//                std::vector<int> counts(group_num);
//                for (auto x : ids.second) counts[x]++;
//                std::vector<std::vector<int>> groups(ids.first);
//                for (int i = 0; i < group_num; i++) {
//                    groups[i].reserve(counts[i]);
//                }
//                for (int i = 0; i < _n; i++) {
//                    groups[ids.second[i]].push_back(i);
//                }
//                return groups;
//            }
//
//        private:
//            int _n;
//            struct edge {
//                int to;
//            };
//            std::vector<std::pair<int, edge>> edges;
//        };
//
//    }  // namespace internal
//
//}  // namespace atcoder
//
//
//namespace atcoder {
//    struct scc_graph {
//    public:
//        scc_graph() : internal(0) {}
//        scc_graph(int n) : internal(n) {}
//
//        void add_edge(int from, int to) {
//            int n = internal.num_vertices();
//            internal.add_edge(from, to);
//        }
//
//        std::vector<std::vector<int>> scc() { return internal.scc(); }
//
//    private:
//        internal::scc_graph internal;
//    };
//}
//
//struct UnionFind {
//private:
//    const int n;
//    int __size;
//    vector<int> uf;
//public:
//    // 初期化 UnionFind uni(n) のように宣言すれば良い
//    UnionFind(int _n) : n(_n), __size(_n), uf(_n, -1) {}
//    // find (木の根を求める)
//    int find(int x) { return (uf[x] < 0) ? x : uf[x] = find(uf[x]); }
//    // x と y が同じ集合に属するかどうか
//    bool same(int x, int y) { return find(x) == find(y); }
//    // x が属する集合の要素数
//    int size(int x) { return -uf[find(x)]; }
//    // 集合はいくつあるか
//    int size() { return __size; }
//    // x と y の属する集合を併合
//    bool unite(int x, int y) {
//        x = find(x); y = find(y);
//        if (x == y) return false;
//        __size--;
//        if (uf[y] < uf[x]) swap(x, y);
//        uf[x] += uf[y]; uf[y] = x;
//        return true;
//    }
//};
//
//using ll = long long;
//
//struct Edge {
//    ll from; // 移動前のノード
//    ll to; // 移動先のノード
//    ll cost; // 辺のコスト
//    ll hoge; // 任意変更 いらないかも
//
//    Edge() = default;
//    Edge(ll _to) : from(-1), to(_to), cost(1), hoge(-1) {};
//    Edge(ll _to, ll _cost) : from(-1), to(_to), cost(_cost), hoge(-1) {};
//    Edge(ll _from, ll _to, ll _cost) : from(_from), to(_to), cost(_cost), hoge(-1) {};
//    Edge(ll _from, ll _to, ll _cost, ll _hoge) : from(_from), to(_to), cost(_cost), hoge(_hoge) {};
//    bool operator< (const Edge& rhs) const {
//        return cost < rhs.cost;
//    }
//    bool operator> (const Edge& rhs) const {
//        return cost > rhs.cost;
//    }
//    bool operator==(const Edge& rhs) const {
//        if (from != rhs.from) return false;
//        if (to != rhs.to) return false;
//        if (cost != rhs.cost) return false;
//        if (hoge != rhs.hoge) return false;
//        return true;
//    }
//    bool operator!=(const Edge& rhs) const {
//        if (from != rhs.from) return true;
//        if (to != rhs.to) return true;
//        if (cost != rhs.cost) return true;
//        if (hoge != rhs.hoge) return true;
//        return false;
//    }
//};
//
//using Graph = vector<vector<Edge>>;
//
//// LCA ２つのノードを渡して最小共通祖先を求める
//// 根付き木構造で使える Lowest Common Ancestor
//class LCA {
//public:
//    LCA(const Graph& G, int root = 0) {
//        Init(G, root);
//    }
//
//    // ２つの頂点の最小共通祖先を求める
//    int GetAncestor(int u, int v) {
//        if (dist[u] < dist[v]) swap(u, v);
//        int k = parent.size();
//        // LCAまでの距離を同じにする
//        for (int i = 0; i < k; ++i) {
//            if ((dist[u] - dist[v]) >> i & 1) u = parent[i][u];
//        }
//
//        // 二分探索でLCAを求める
//        if (u == v) return u;
//        for (int i = k - 1; i >= 0; --i) {
//            if (parent[i][u] != parent[i][v]) {
//                u = parent[i][u];
//                v = parent[i][v];
//            }
//        }
//        return parent[0][u];
//    }
//
//    // ２点間の距離を求める
//    int GetDist(int u, int v) {
//        return dist[u] + dist[v] - 2 * dist[GetAncestor(u, v)];
//    }
//
//    // 二点間のパス上に指定した頂点がある
//    bool IsOnPath(int u, int v, int a) {
//        return GetDist(u, a) + GetDist(a, v) == GetDist(u, v);
//    }
//
//private:
//    // 初期化
//    void Init(const Graph& G, int root = 0) {
//        int v = G.size();
//        int k = 1;
//        while ((1 << k) < v) ++k;
//        parent.assign(k, vector<int>(v, -1));
//        dist.assign(v, -1);
//        dfs(G, root, -1, 0);
//        for (int i = 0; i + 1 < k; ++i) {
//            for (int j = 0; j < v; ++j) {
//                if (parent[i][j] < 0) parent[i + 1][j] = -1; // 親の場合
//                else parent[i + 1][j] = parent[i][parent[i][j]]; // ダブリンぐ
//            }
//        }
//    }
//
//    // 根からの距離と一つ先の頂点を求める
//    void dfs(const Graph& G, int v, int p, int d) {
//        parent[0][v] = p;
//        dist[v] = d;
//        for (auto e : G[v]) {
//            if (e.to != p) dfs(G, e.to, v, d + 1);
//        }
//    }
//
//    vector<vector<int>> parent; // parent[k][u] := uの2^k先の親
//    vector<int> dist; // rootからの距離
//};
//
//
//
//
//int main() {
//
//    int n, m;
//    cin >> n >> m;
//
//    atcoder::scc_graph scc(n);
//
//    vector<pair<int, int>> ab(m);
//    for (int i = 0; i < m; ++i) {
//        cin >> ab[i].first >> ab[i].second;
//        --ab[i].first;
//        --ab[i].second;
//        scc.add_edge(ab[i].first, ab[i].second);
//    }
//
//    auto graph = scc.scc();
//
//    int nodeNum = graph.size();
//
//    UnionFind uni(n);
//
//    // 互いに行き来できるノード同士を集合化
//    for (int i = 0; i < nodeNum; ++i) {
//        bool first = true;
//        for (auto node : graph[i]) {
//            if (first) {
//                first = false;
//                continue;
//            }
//            uni.unite(node, graph[i][0]);
//        }
//    }
//
//    // 根とインデックスをつなぐ
//    map<int, int> mp;
//    {
//        int cnt = 0;
//        for (auto& nodes : graph) {
//            mp[uni.find(nodes[0])] = cnt++;
//        }
//    }
//
//    Graph G(nodeNum);
//    {
//        vector<vector<int>> tmp(nodeNum, vector<int>());
//        for (auto [a, b] : ab) {
//            int from = mp[uni.find(b)];
//            int to = mp[uni.find(a)];
//            tmp[from].emplace_back(to);
//        }
//        // 重複分削除
//        for (auto& v : tmp) {
//            sort(v.begin(), v.end());
//            v.erase(unique(v.begin(), v.end()), v.end());
//        }
//
//        // コピー
//        for (int i = 0; i < nodeNum; ++i) {
//            for (auto to : tmp[nodeNum]) {
//                G[i].emplace_back(to);
//            }
//        }
//    }
//
//    UnionFind uni2(nodeNum);
//    {
//        for (auto& nodes : G) {
//            for (auto& edge : nodes) {
//                uni2.unite(edge.from, edge.to);
//            }
//        }
//    }
//
//    // LCA大量生成
//    vector<LCA> v_lca(uni2.size());
//    vector<map<int, int>> v_mp(uni2.size());
//    vector<int> v_cnt(uni2.size(), 0);
//    {
//        for (auto [a, b] : ab) {
//            int from = mp[uni.find(b)];
//            int to = mp[uni.find(a)];
//
//        }
//    }
//
//    // 準備OK
//
//    int q;
//    cin >> q;
//    vector<bool> ans;
//
//    int cur = uni.find(0);
//
//    for (int i = 0; i < q; ++i) {
//        int x, y;
//        cin >> x >> y;
//        --y;
//
//        // 移動
//        if (x == 1) {
//            cur = uni.find(y);
//        }
//        else { // 行けるか
//
//            // 互いに行き来できるか
//            if (uni.same(cur, y)) {
//                ans.emplace_back(true);
//            }
//
//            bool can = true;
//
//            int from = mp[uni.find(y)];
//            int to = mp[uni.find(cur)];
//
//            // from から to にいけるか
//        }
//
//    }
//
//    for (auto b : ans) cout << (b ? "YES" : "NO") << endl;
//
//    return 0;
//}