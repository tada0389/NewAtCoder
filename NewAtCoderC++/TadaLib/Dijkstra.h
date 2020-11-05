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
// 0~3�܂ł͉E������ 4~7�܂ł͎΂�
constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };

namespace {
    template<typename T> void chmax(T& a, T b) { a = std::max(a, b); }
    template<typename T> void chmin(T& a, T b) { a = std::min(a, b); }
    template<typename T> void chadd(T& a, T b) { a = a + b; }

    void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; i++) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }

    // �W�����o��
    struct Read {
        std::size_t sz;
        Read(std::size_t _sz = 1) : sz(_sz) {}
        template <typename T> operator T () const { T a; std::cin >> a; return a; }
        template <typename T> operator std::vector<T>() const { std::vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
    };

    // 2�����p�̕W�����o��
    template<typename T>
    struct inpn {
        std::size_t szi, szj;
        inpn(std::size_t _szi, std::size_t _szj) : szi(_szi), szj(_szj) {}
        operator std::vector<std::vector<T>>() const {
            std::vector<std::vector<T>> a(szi, std::vector<T>(szj));
            for (std::size_t i = 0; i < szi; ++i)
                for (std::size_t j = 0; j < szj; ++j) cin >> a[i][j];
            return a;
        }
    };

    Read inp1; // input one

    // �a�{���玩���Ȃ�ɉ���

    struct Edge {
        ll from; // �ړ��O�̃m�[�h
        ll to; // �ړ���̃m�[�h
        ll cost; // �ӂ̃R�X�g
        ll hoge; // �C�ӕύX ����Ȃ�����

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

    // �_�C�N�X�g���@ O(ElogV)
    vector<ll> dijkstra(ll start, const Graph& G) {
        vector<ll> dist(G.size(), infll);
        // �ӂ̃R�X�g�����������Ɏ��o���@�ꍇ�ɉ����ĕύX
        priority_queue<Edge, vector<Edge>, greater<Edge>> que;
        //queue<Edge> que; // �R�X�g�����ׂ�1�̏ꍇ�͕��ʂ�bfs�ɂ��� �R�����g�A�E�g���悤

        dist[start] = 0; // dist[i] := start->i�܂ł̍ŒZ����
        que.push(Edge(start, 0));

        while (!que.empty()) {
            ll cost, u; // ���܂łɂ����������ԁ@���݂̒��_
            cost = que.top().cost, u = que.top().to;
            //cost = que.front().cost, u = que.front().to;
            que.pop();
            if (dist[u] < cost) continue;
            for (auto& e : G[u]) {
                ll v = e.to;
                ll new_cost = cost + e.cost;

                if (dist[v] <= new_cost) continue;

                dist[v] = new_cost;
                que.push(Edge(v, new_cost));
            }
        }
        return dist;
    }

    // �P���ȓ��͂̃O���t��ǂݎ�� 
    Graph ReadGraph(int n, int m, bool zeroStart = false) {
        Graph G(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            if (!zeroStart) --u, --v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }

        return G;
    }

}

int main() {

    ll n, m, s;
    cin >> n >> m >> s;

    vector<ll> u(m), v(m), a(m), b(m);
    rep(i, m) {
        cin >> u[i] >> v[i] >> a[i] >> b[i];
        --u[i], --v[i];
    }
    vector<ll> c(n), d(n);
    rep(i, n) {
        cin >> c[i] >> d[i];
    }

    const ll kMax = 2510;
    chmin(s, kMax - 1);

    Graph G(n * kMax);

    vector<vector<int>> to_node(n, vector<int>(kMax));

    int to_index = 0;
    rep(i, n) {
        rep(j, kMax) {
            to_node[i][j] = to_index++;
        }
    }

    // �ꏊ���قȂ�m�[�h�ւ̕ӂ��\��
    rep(i, m) {
        rep(j, kMax) { // ���݋��j�������Ă���Ƃ��ɂǂ��ړ��ł��邩
            if (j - a[i] < 0) continue; // ��݂�����Ȃ�
            int from = to_node[u[i]][j];
            int to = to_node[v[i]][j - a[i]];
            G[from].push_back(Edge(to, b[i]));
            from = to_node[v[i]][j];
            to = to_node[u[i]][j - a[i]];
            G[from].push_back(Edge(to, b[i]));
        }
    }

    // �ꏊ�͓��������K�w���قȂ�m�[�h�ւ̕ӂ��\��
    rep(i, n) {
        rep(j, kMax) { // ���݋��j�������Ă���Ƃ��ɂǂ��ړ��ł��邩
            int from = to_node[i][j];
            int to = to_node[i][min(j + c[i], kMax - 1)];
            G[from].push_back(Edge(to, d[i]));
        }
    }

    auto dist = dijkstra(to_node[0][s], G);


    Rep(i, 1, n) {
        ll ans = infll;
        rep(j, kMax) {
            chmin(ans, dist[to_node[i][j]]);
        }
        Cout(ans);
    }

    // �ӂ̐��ɒ���

    return 0;
}
