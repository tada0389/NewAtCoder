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
constexpr ll mod = 998244353;
// 0~3‚Ü‚Å‚Í‰E¶‰ºã 4~7‚Ü‚Å‚ÍŽÎ‚ß
constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };

namespace {
    template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
    template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

    void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; ++i) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }

    // •W€“üo—Í
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

    struct Element {
        int value;
        int id;
        int id2;

        Element() = default;
        Element(int left, int right, int index) : value(left), id(right), id2(index) {};
        bool operator< (const Element& rhs) const {
            return true;
        }
    };
}

int main() {



    return 0;
}


int main() {

    int l, r, d; Reads(l, r, d);
    int ans = 0;
    for (int i = l; i <= r; ++i) {
        if (i % d == 0) ++ans;
    }
    Write(ans);

    return 0;
}

int main() {

    int n = read;
    vector<int> a = Read(n);

    int ans = 0;
    for (int i = 0; i < n; i += 2) {
        if (a[i] % 2 == 1) ++ans;
    }
    Write(ans);

    return 0;
}

int main() {

    int n = read;

    vector<ll> ans(n, 0LL);
    rep(i, n) {
        int v = i + 1;

        int res = 0;
        const int kMax = 102;
        Rep(x, 1, kMax) {
            Rep(y, 1, kMax) {
                Rep(z, 1, kMax) {
                    int value = x * x + y * y + z * z + x * y + y * z + z * x;
                    if (value == v) {
                        ++res;
                    }
                }
            }
        }
        ans[i] = res;
    }

    Write(ans, "\n");

    return 0;
}

