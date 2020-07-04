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
        template <typename T> operator std::vector<T>() const { std::vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
    };

    // 2次元用の標準入出力
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

    inp inp1; // input one

    // けんちょんさんのを自分なりに改造 tada
    // Combination を高速にテーブル化させるライブラリ
    // MOD >= 1 の場合は，MODで割った余りを返す 構築 O(n) 取得 O(1)
    // MOD <= 0 の場合は，余りを考慮しない 構築 O(n^2) 取得 O(1) オーバーフローに注意
    template<int MOD> class COM {
    public:
        COM(long long max_n = 2e6) noexcept : kMax_(max_n * 4LL + 1LL) {
            if (MOD >= 1) Init();
            else InitNoMod();
        };

        //　二項係数計算
        long long Com(int n, int k) {
            if (n < k) return 0LL;
            if (n < 0 || k < 0) return 0LL;
            if (MOD >= 1) return fac_[n] * (finv_[k] * finv_[n - k] % MOD) % MOD;
            else return com_table_[n * kMax_ + k];
        }

        // 重複組み合わせ
        long long H(int n, int k) {
            return Com(n + k - 1, k);
        }


    private:
        void Init() {
            fac_.resize(kMax_);
            finv_.resize(kMax_);
            inv_.resize(kMax_);

            fac_[0] = fac_[1] = 1;
            finv_[0] = finv_[1] = 1;
            inv_[1] = 1;

            for (int i = 2; i < kMax_; ++i) {
                fac_[i] = fac_[i - 1] * i % MOD;
                inv_[i] = MOD - inv_[MOD % i] * (MOD / i) % MOD;
                finv_[i] = finv_[i - 1] * inv_[i] % MOD;
            }
        }
        void InitNoMod() {
            com_table_ = std::vector<long long>(kMax_ * kMax_, 0LL);

            for (int i = 0; i < kMax_; ++i) {
                for (int j = 0; j <= i; ++j) {
                    if (j == 0 || j == i) com_table_[i * kMax_ + j] = 1LL;
                    else {
                        com_table_[i * kMax_ + j] =  // パスカルの三角形を利用している
                            (com_table_[(i - 1) * kMax_ + j - 1] + com_table_[(i - 1) * kMax_ + j]);
                    }
                }
            }

            //rep(i, kMax_) {
            //    rep(j, i + 1) {
            //        cout << com_table_[i * kMax_ + j] << " ";
            //    }
            //    cout << endl;
            //}
        }

        std::vector<long long> fac_, finv_, inv_;
        std::vector<long long> com_table_;
        const long long kMax_;
    };

    // C(n, 0) + C(n, 1) + C(n, 2) + ... + C(n, n) = 2^n
    // 2^n = (1 + 1)^n = ΣC(n, k) * 1^k * 1^(n - k) より

    // 0 * C(n, 0) + 1 * C(n, 1) + 2 * C(n, 2) + ... + n * C(n, n) = n2^(n-1)
    // C(n, k) = n/k * C(n - 1, k - 1) より
    // n * C(n-1,0) + n * C(n-1,1) + n * C(n-2,2) + ... + n * C(n - 1, n - 1) = n * 2^(n - 1)
}

//int main() {
//
//    int n, a, b;
//    cin >> n >> a >> b;
//    vector<ll> v = inp(n);
//
//    // A個以上 B個以下選ぶ
//
//    COM<-1> com(n);
//
//    sort(allof(v));
//
//    ll sum = 0LL;
//    rep(i, a) sum += v[n - 1 - i];
//
//    cout << fixed << setprecision(-7) << (double)sum / a << endl;
//
//    // 次に何通りか
//
//    ll ans = 0LL;
//
//    // 境界の値
//    ll boader = v[n - a];
//
//    // この値がいくつ選ばれて，いくつ残っているか
//    ll boader_num = 0LL;
//    ll used_num = 0LL;
//    rep(i, n) {
//        if (v[i] == boader) {
//            ++boader_num;
//            if (i >= n - a) ++used_num;
//        }
//    }
//
//    if (sum == boader * a) { // すべて同じ値で構成されている
//        // 何個選ぶか
//        for (int i = a; i <= b; ++i) {
//            // i個選ぶ
//            if (i > boader_num) break;
//            ans += com.Com(boader_num, i);
//        }
//    }
//    else {
//        ans = com.Com(boader_num, used_num);
//    }
//
//    Cout(ans);
//
//    return 0;
//}

int main() {

    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    // f(r, c) = COM(r + c, r)

    int height = r2;
    int width = c2;
    COM<mod> com(height + width);

    ll ans = 0LL;

    // S(p) = C(1, y) + C(2, y) + ... + C(p, y) として (もちろんC(a, b) かつ a < b  = 0)
    // S(b) - S(a - 1) を計算するのが定石らしい
    // さらに
    // S(p) = C(p + 1, y + 1) が成り立つらしい パスカルの三角形を見るとわかりやすい
    // C(p + 1, y + 1) = C(1, y) + C(2, y) + ... C(p, y)

    for (int i = r1; i <= r2; ++i) {
        ans += (com.Com(c2 + i + 1, i + 1) - com.Com(c1 + i, i + 1) + mod) % mod;
        ans %= mod;
        //for (int j = c1; j <= c2; ++j) {
        //    ans += com.Com(i + j, i);
        //    ans %= mod;
        //}
    }

    Cout(ans);

    return 0;
}
