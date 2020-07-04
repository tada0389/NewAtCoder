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

    // 標準出力
    void Out(long long x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Out(const T& x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Out(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; ++i) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }
    template <typename T> void Out(const std::vector<std::vector<T>>& x, const char* sep = " ", const char* end = "\n") { for (auto v : x) Out(v, sep, end); }

    // 標準入力
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
}

int main() {

    int n, x;
    cin >> n >> x;
    vector<ll> a = inp(n);

    //　左から貪欲でいいよな

    ll ans = 0;

    vector<ll> sum(n, 0);
    rep(i, n - 1) sum[i] = a[i] + a[i + 1];

    rep(i, n - 1) {
        if (sum[i] > x) {
            int add = sum[i] - x;
            sum[i + 1] -= add;
            ans += add;
        }
    }

    Out(ans);

    return 0;
}
