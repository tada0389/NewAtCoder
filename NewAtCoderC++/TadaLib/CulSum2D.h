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

        // Bit���Z���y�ɂ��郉�C�u���� �Q�i��
    // @author tada
    class Bit {
    public:
        // �R���X�g���N�^�ŃT�C�Y��
        Bit(int length) {
            length_ = length;
            bit_ = -1; // while(bit.next()) �������̂�z��
        }

        // ���̒l�Ɉړ����� �������ɐi�߂Ȃ��Ȃ��false��Ԃ�
        bool Next() {
            if (++bit_ >= (1 << length_)) return false;
            return true;
        }

        // Bit���� �w�肵���C���f�b�N�X��ύX����
        void Change(int i, int value = 1) {
            if (value == 1) bit_ |= (1 << i);
            else bit_ &= ~(1 << i);
        }

        // �w�肵���C���f�b�N�X��1���ǂ���
        bool IsSelected(int i) {
            return bit_ & (1 << i);
        }

        // 1�̌���Ԃ� �����Ŕ͈� [l, r)
        int GetSelectedNum(int l, int r) {
            int res = 0;
            for (int i = l; i < r; ++i) {
                if (IsSelected(i)) ++res;
            }
            return res;
        }

        // �r�b�g���int�^�ŕԂ�
        int GetBit() {
            return bit_;
        }

        // �r�b�g����Ԃ�
        int GetLength() {
            return length_;
        }

    private:
        int bit_;
        int length_;
    };


    //ganariya
    template<class T>
    class CulSum2D {
    private:
        //original
        int H, W;

        //original+1
        vector<vector<T>> data;

    public:

        /// @param _H original
        /// @param _W original
        CulSum2D(int _H, int _W) :
            H(_H), W(_W) {
            reset();
        }

        void reset() {
            data = vector<vector<T>>(H + 1, vector<T>(W + 1, T{}));
        }

        /// 0-index
        /// @param y original
        /// @param x original
        /// @param d original
        void add(T y, T x, T d) {
            y++;
            x++;
            if (y >= H + 1 || x >= W + 1) return;
            data[y][x] += d;
        }

        void build() {
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    data[i + 1][j + 1] += data[i + 1][j] + data[i][j + 1] - data[i][j];
                }
            }
        }

        /// 0-index
        /// @param sy original close
        /// @param sx original close
        /// @param ty original open
        /// @param tx original open
        T get(int sy, int sx, int ty, int tx) {
            return data[ty][tx] - data[ty][sx] - data[sy][tx] + data[sy][sx];
        }

    };

    // �ݐϘa
    CulSum2D<int> sum(10, 1000);

    struct Square {
    public:
        Square(int sy, int sx, int ty, int tx) :
            sy_(sy), sx_(sx), ty_(ty), tx_(tx) {
        }

        int Get() {
            return sum.get(sy_, sx_, ty_, tx_);
        }

        int sy_, sx_, ty_, tx_;
    };
}

int main() {

    int h, w, k;
    cin >> h >> w >> k;
    vector<vector<int>> s(h, vector<int>(w));
    rep(i, h) {
        rep(j, w) {
            char c = inp1;
            if (c == '0') s[i][j] = 0;
            else s[i][j] = 1;
        }
    }


    rep(i, h) {
        rep(j, w) {
            sum.add(i, j, s[i][j]);
        }
    }
    sum.build();





    int ans = inf;

    Bit bit(h - 1);
    while (bit.Next()) {
        int b = bit.GetBit();

        // �������ɐ؂�ʂ��S�T��
        int num = bit.GetSelectedNum(0, h);
        int tmp_ans = num;

        vector<Square> rects;

        //cout << "bit : " << b << endl;
        //cout << "rect : " << endl;

        int prev = 0;
        rep(i, h - 1) {
            // �؂���
            if (b & (1 << i)) {
                Square s(prev, 0, i + 1, w);
                rects.push_back(s);
                prev = i + 1;
                //Cout(s.Get());
            }
        }
        // �c��
        Square s(prev, 0, h, w);
        rects.push_back(s);
        //Cout(s.Get());
        //cout << "end" << endl;

        //Cout(tmp_ans);
        // �c�����ɂ��؂�
        // ���ׂĖ������̂ɂǂꂭ�炢�K�v��
        // �������×~
        bool ok = true;
        int prev_w = 0;
        rep(j, w) {
            bool out = false;
            rep(i, rects.size()) {
                int s = sum.get(rects[i].sy_, prev_w, rects[i].ty_, j + 1);
                if (s > k) {
                    out = true;
                    break;
                }
            }
            // �����ł���
            if (out) {
                // �����l�}�X�Ń_���Ȃ�O�񂪂�������
                if (prev_w == j) {
                    ok = false;
                    break;
                }
                ++tmp_ans;
                prev_w = j;
            }
        }
        if (ok) chmin(ans, tmp_ans);
        else continue;
    }

    Cout(ans);

    return 0;
}
