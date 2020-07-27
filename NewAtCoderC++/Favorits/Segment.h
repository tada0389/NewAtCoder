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
        template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
        template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
    };

    Read inp1; // input one

    struct Segment {
        ll left, right;
        Segment* prev;
        Segment* next;

        Segment(ll _left, ll _right, Segment* _prev, Segment* _next) :
            left(_left), right(_right), prev(_prev), next(_next) {
        }
    };
}

int main() {

    int n = inp1;
    vector<ll> a = Read(n);

    // �ׂƂ̘a���ł��������Ȃ�g������
    // ���ꂾ�Ƒ�ς�����C���ꂼ��̃X���C�������񍇐�����邩�H
    // �ǂ������DP�Ɏ������ށH �ق��̕��@�v������

    //auto c = [](Segment* lhs, Segment* rhs) {
    //    return (lhs->left + lhs->right) < (rhs->left + rhs->right);
    //};

    //priority_queue <Segment*,vector<Segment*>,decltype(c)> que;

    //// ��ԍ��̃Z�O�����g
    //Segment* seg1 = nullptr;
    //seg1 = new Segment(a[0], a[1], nullptr, nullptr);
    //que.push(seg1);

    //Segment* prev_seg = seg1;

    //Rep(i, 1, n - 1) {
    //    // ���E������
    //    ll left = a[i - 1];
    //    ll right = a[i + 1];

    //    Segment* seg = new Segment(left, right, prev_seg, nullptr);
    //    seg->prev->next = seg;
    //    que.push(seg);
    //    prev_seg = seg;
    //}
    //// ��ԉE�̃Z�O�����g
    //Segment* segn = new Segment(a[n - 2], a[n - 1], prev_seg, nullptr);
    //segn->prev->next = segn;
    //que.push(segn);

    //ll ans = 0LL;
    //while (!que.empty()) {
    //    Segment* min_seg = que.top(); que.pop();
    //    ans += min_seg->left + min_seg->right;
    //    free(min_seg);
    //    //// ����̍��E��ύX
    //    //min_seg->prev->right += min_seg->right;
    //    //min_seg->next->left += min_seg->left; // �����ȁC����
    //}

    //Cout(ans);

    return 0;
}

/*
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
    struct inp {
        std::size_t sz;
        inp(std::size_t _sz = 1) : sz(_sz) {}
        template <typename T> operator T () const { T a; std::cin >> a; return a; }
        template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
        template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
    };

    inp inp1; // input one

    vector<vector<ll>> dp; // first: �R�X�g�̍��v�̍ŏ��l

    // �������ċA [l, r)
    ll rec(int l, int r, const vector<ll>& a, const vector<ll>& sum) {
        if (r - l == 1) {
            dp[l][r] = 0;
            return 0;
        }
        ll val = infll;
        Rep(i, l + 1, r) {
            ll tmp = 0LL;
            if (dp[l][i] == infll) rec(l, i, a, sum);
            if (dp[i][r] == infll) rec(i, r, a, sum);
            tmp = dp[l][i] + dp[i][r] + sum[r] - sum[l];
            chmin(val, tmp);
        }
        dp[l][r] = val;
        return val;
    }
}

int main() {

    int n = inp1;
    vector<ll> a = inp(n);

    // �ׂƂ̘a���ł��������Ȃ�g������
    // ���ꂾ�Ƒ�ς�����C���ꂼ��̃X���C�������񍇐�����邩�H
    // �ǂ������DP�Ɏ������ށH

    // ���ׂ�
    // ���DP�Ƃ����̂�����炵��

    // dp[l][r] := ���[l, r) �ɂ��āC�P�ɂȂ�܂ő�����s�����Ƃ��̎x�����R�X�g�̍��v�̍ŏ��l
    // dp[l][r] = min(dp[l][i] + dp[i][r] + �u���[l, r)�̍��v�l)
    // DP�e�[�u��������Ă�悤�Ȃ���H

    // ���S����

    dp.assign(n + 1, vector<ll>(n + 1, infll));
    //dp = vector<vector<pair<ll, ll>>>(n, vector<pair<ll, ll>>(n, make_pair(inf, inf)));

    // �ݐϘa
    vector<ll> sum(n + 1, 0LL);
    rep(i, n) {
        sum[i + 1] = sum[i] + a[i];
    }

    Cout(rec(0, n, a, sum));

    return 0;
}
*/