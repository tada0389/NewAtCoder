#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <sstream>
#include <cmath>
#include <numeric>
#include <stack>
#include <iomanip>
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
    template<typename T> bool chmax(T& a, T b) { if (a <= b) { a = b; return true; } return false; }
    template<typename T> bool chmin(T& a, T b) { if (a >= b) { a = b; return true; } return false; }

    void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
    template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; i++) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }

    // �W�����o��
    struct inp {
        std::size_t sz;
        inp(std::size_t _sz = 1) : sz(_sz) {}
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

    inp inp1; // input one

        // ���񂿂�񂳂�̂��������� tada
    // Combination �������Ƀe�[�u���������郉�C�u����
    // MOD >= 1 �̏ꍇ�́CMOD�Ŋ������]���Ԃ� O(n)
    // MOD <= 0 �̏ꍇ�́C�]����l�����Ȃ� O(n^2) �I�[�o�[�t���[�ɒ���
    template<int MOD> class COM {
    public:
        COM(long long max_n = 2e6) noexcept : kMax_(max_n * 4LL + 1LL) {
            if (MOD >= 1) Init();
            else InitNoMod();
        };

        //�@�񍀌W���v�Z
        long long Com(int n, int k) {
            if (n < k) return 0LL;
            if (n < 0 || k < 0) return 0LL;
            if (MOD >= 1) return fac_[n] * (finv_[k] * finv_[n - k] % MOD) % MOD;
            else return com_table_[n * kMax_ + k];
        }

        // �d���g�ݍ��킹
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
                inv_[i] = MOD - inv_[mod % i] * (MOD / i) % MOD;
                finv_[i] = finv_[i - 1] * inv_[i] % MOD;
            }
        }
        void InitNoMod() {
            com_table_ = std::vector<long long>(kMax_ * kMax_, 0LL);

            for (int i = 0; i < kMax_; ++i) {
                for (int j = 0; j <= i; ++j) {
                    if (j == 0 || j == i) com_table_[i * kMax_ + j] = 1LL;
                    else {
                        com_table_[i * kMax_ + j] =  // �p�X�J���̎O�p�`�𗘗p���Ă���
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
}

// ����������p�������
// https://atcoder.jp/contests/abc003/tasks/abc003_4
int main() {

    ll r, c;
    cin >> r >> c;
    ll x, y;
    cin >> x >> y;
    ll d, l;
    cin >> d >> l;

    ll base = (r - x + 1) * (c - y + 1);

    COM<mod> com;

    // �f�X�N�ƃ��b�N����ʂ��Ȃ�
    base *= com.Com(d + l, d);
    base %= mod;

    // ��͂ǂ��ɒu����

    // �S�̂���_���ȃP�[�X�������
    ll ans = 0LL;

    //ans -= com.Com((x - 1) * y, d + l) * 2; // ���@�E
    //ans -= com.Com((y - 1) * x, d + l) * 2; // ���@��
    //ans += com.Com(x * (y - 2), d + l); // �㉺
    //ans += com.Com(y * (x - 2), d + l); // �E��
    //ans += com.Com((x - 1) * (y - 1), d + l) * 4; // ���E�@��E�@�������@�㍶
    //ans -= com.Com((x - 1) * (y - 2), d + l) * 2; // ���㉺ �E�㉺
    //ans -= com.Com((y - 1) * (x - 2), d + l) * 2; // ���E�� ���E��
    //ans += com.Com((y - 2) * (x - 2), d + l); // ���E�㉺

    // �������bit�ŊǗ����₷���炵��
    rep(bit, (1 << 4)) {
        int tx = x;
        int ty = y;

        if ((bit >> 0) & 1) --tx;
        if ((bit >> 1) & 1) --tx;
        if ((bit >> 2) & 1) --ty;
        if ((bit >> 3) & 1) --ty;

        if (tx < 0 || ty < 0) continue;

        // 1�̌��������Ȃ���Z
        // 1�̌�����Ȃ猸�Z

        if (__builtin_popcount(bit) % 2 == 0) ans += com.Com(tx * ty, d + l);
        else ans -= com.Com(tx * ty, d + l);

        ans = (ans + mod) % mod;
    }

    ans *= base;
    ans %= mod;

    Cout(ans);

    // �����

    return 0;
}