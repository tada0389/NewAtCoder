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
// 0~3�܂ł͉E������ 4~7�܂ł͎΂�
constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };

namespace {
    template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
    template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

    void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; ++i) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }

    // �W�����o��
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

    // �a�{���玩���Ȃ�ɉ���
    // �v�Z�� E A(n)

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

    using Graph = std::vector<Edge>;

    struct UnionFind {
    private:
        const int n;
        int __size;
        std::vector<int> uf;
    public:
        // ������ UnionFind uni(n) �̂悤�ɐ錾����Ηǂ�
        UnionFind(int _n) : n(_n), __size(_n), uf(_n, -1) {}
        // find (�؂̍������߂�)
        int find(int x) { return (uf[x] < 0) ? x : uf[x] = find(uf[x]); }
        // x �� y �������W���ɑ����邩�ǂ���
        bool same(int x, int y) { return find(x) == find(y); }
        // x ��������W���̗v�f��
        int size(int x) { return -uf[find(x)]; }
        // �W���͂������邩
        int size() { return __size; }
        // x �� y �̑�����W���𕹍�
        bool unite(int x, int y) {
            x = find(x); y = find(y);
            if (x == y) return false;
            __size--;
            if (uf[y] < uf[x]) swap(x, y);
            uf[x] += uf[y]; uf[y] = x;
            return true;
        }
    };

    // �ŏ��S��؂����߂� first�͍ŏ��R�X�g second�͕K�v�ȕӂ̐�
    std::pair<ll, int> Kruskal(Graph& G, const int n) {
        // �ӂ̃R�X�g�����������ɕ��ׂ�
        std::sort(G.begin(), G.end());
        UnionFind uni(n);

        std::pair<ll, int> res;
        for (int i = 0, sz = G.size(); i < sz; ++i) {
            Edge e = G[i];
            // ���łɓ����O���[�v�Ȃ�q���Ȃ�
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

    // |x2 - x1| �̕ӂ� |y2 - y1| �̕ӂ��l����
    // |x3 - x1| �̕ӂ� |x3 - x2| + |x2 - x1| �Ȃ̂ŕK�v�Ȃ�

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
