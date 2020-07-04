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

    struct SCC {
        const int n;
        std::vector<bool> isthrough;
        std::vector<int> vs, cmp;
        std::vector<std::vector<int> > G, rG, H;

        SCC(int n_) : n(n_),
            isthrough(n, false), cmp(n, 0), G(n), rG(n) {}
        void add_edge(int u, int v) {
            G[u].emplace_back(v);
            rG[v].emplace_back(u);
        }

        void SCC_dfsone(int cur) {
            isthrough[cur] = true;
            for (std::size_t i = 0; i < G[cur].size(); i++) {
                if (!isthrough[G[cur][i]]) {
                    SCC_dfsone(G[cur][i]);
                }
            }
            vs.emplace_back(cur);
        }

        void SCC_dfstwo(std::vector<int>& vec, int cur, int k) {
            cmp[cur] = k;
            isthrough[cur] = true;
            vec.emplace_back(cur);
            for (std::size_t i = 0; i < rG[cur].size(); i++) {
                if (!isthrough[rG[cur][i]]) {
                    SCC_dfstwo(vec, rG[cur][i], k);
                }
            }
        }

        // 強結合成分連結の数を求める
        int scc() {
            for (int i = 0; i < n; i++) {
                if (!isthrough[i]) SCC_dfsone(i);
            }

            fill(isthrough.begin(), isthrough.end(), false);
            std::reverse(vs.begin(), vs.end());
            int k = 0; std::vector<std::vector<int>> S;

            for (std::size_t i = 0; i < vs.size(); i++) {
                if (!isthrough[vs[i]]) {
                    S.emplace_back(std::vector<int>());
                    SCC_dfstwo(S.back(), vs[i], k++);
                }
            }

            return k;
        }
    };
}

// https://codeforces.com/gym/102091/attachments/download/8314/20182019-acmicpc-asia-nakhon-pathom-regional-contest-en.pdf
int main() {

    int q = inp1;

    vector<int> ans(q);

    rep(t, q) {
        int n = inp1;
        int e = inp1;
        SCC scc(n);
        rep(i, e) {
            int a, b;
            cin >> a >> b;
            scc.add_edge(a, b);
        }

        int res = scc.scc();

        ans[t] = res;
    }

    rep(i, q) {
        Cout(ans[i]);
    }

    return 0;
}
