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
// 0~3�܂ł͉E������ 4~7�܂ł͎΂�
constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };

namespace {
    template<typename T> void chmax(T& a, T b) { a = std::max(a, b); }
    template<typename T> void chmin(T& a, T b) { a = std::min(a, b); }
    template<typename T> void chadd(T& a, T b) { a = a + b; }

    template <typename T> void Cout(T& x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; i++) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }


    // �W�����o��
    struct inp {
        size_t sz;
        inp(size_t _sz = 1) : sz(_sz) {}
        template <typename T> operator T () const { T a; std::cin >> a; return a; }
        template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
        template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
    };

    inp inp1; // input one

    struct UnionFind {
    private:
        const int n;
        int __size;
        vector<int> uf;
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

    using Graph = vector< vector<int> >;
}

// https://atcoder.jp/contests/abc157/tasks/abc157_d
//int main() {
//
//	int n, m, k;
//	cin >> n >> m >> k;
//	vector<int> a(m), b(m);
//	rep(i, m) cin >> a[i] >> b[i];
//	vector<int> c(k), d(k);
//	rep(i, k) cin >> c[i] >> d[i];
//	rep(i, m) --a[i], --b[i];
//	rep(i, k) --c[i], --d[i];
//
//	// �F�l���̐�
//	vector<int> ans(n, 0);
//
//	UnionFind uni_friend(n);
//	vector<int> close(n, 0);
//	rep(i, m) {
//		++close[a[i]];
//		++close[b[i]];
//	}
//
//	rep(i, m) {
//		// �F�l�֌W�\�z
//		uni_friend.unite(a[i], b[i]);
//	}
//
//	// �����킩��΂���
//	vector<vector<int>> enemy(n, vector<int>());
//	rep(i, k) {
//		enemy[c[i]].push_back(d[i]);
//		enemy[d[i]].push_back(c[i]);
//	}
//
//	// ���������߂�
//	rep(i, n) {
//		ans[i] = uni_friend.size(i) - close[i] - 1;
//		rep(j, enemy[i].size()) {
//			if (uni_friend.same(i, enemy[i][j])) {
//				--ans[i];
//			}
//		}
//	}
//
//	Cout(ans);
//
//	return 0;
//}