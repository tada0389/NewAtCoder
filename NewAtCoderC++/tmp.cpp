//#include <iostream>
//#include <string>
//#include <algorithm>
//#include <vector>
//#include <queue>
//#include <map>
//#include <unordered_map>
//#include <set>
//#include <unordered_set>
//#include <cmath>
//#include <numeric>
//#include <iomanip>
//#include <stack>
//#include <complex>
//#include <functional>
//#include <tuple>
//
//using namespace std;
//
//#define Rep(i,a,b) for(ll i = a; i < b; ++i)
//#define rep(i,b) Rep(i,0,b)
//#define allof(a) (a).begin(), (a).end()
//
//#define Yes(q) ((q) ? "Yes" : "No")
//#define YES(q) ((q) ? "YES" : "NO")
//#define Possible(q) ((q) ? "Possible" : "Impossible")
//#define POSSIBLE(q) ((q) ? "POSSIBLE" : "IMPOSSIBLE")
//
//using ll = long long;
//
//constexpr int inf = 1e9 + 7;
//constexpr ll infll = 1ll << 60ll;
//constexpr ll mod = 1e9 + 7;
//// 0~3�܂ł͉E������ 4~7�܂ł͎΂�
//constexpr int dx[] = { 1, 0, -1, 0, 1, -1 };
//constexpr int dy[] = { 0, 1, 0, -1, 1, 1 };
//
//namespace {
//    template<typename T> bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
//    template<typename T> bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }
//
//    void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
//    template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
//    template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") { for (std::size_t i = 0, sz = x.size(); i < sz; ++i) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }
//
//    // �W�����o��
//    struct inp {
//        std::size_t szi, szj;
//        inp(std::size_t _szi = 1, std::size_t _szj = 1) : szi(_szi), szj(_szj) {}
//        template <typename T> operator T () const { T a; std::cin >> a; return a; }
//        template <typename T> operator std::vector<T>() const { std::vector<T> a(szi); for (std::size_t i = 0; i < szi; ++i) std::cin >> a[i]; return a; }
//        template <typename T> operator std::vector<std::vector<T>>() const {
//            std::vector<std::vector<T>> a(szi, std::vector<T>(szj));
//            for (std::size_t i = 0; i < szi; ++i) for (std::size_t j = 0; j < szj; ++j) cin >> a[i][j]; return a;
//        }
//    };
//    inp inp1;
//
//    //int score_down[26]; // �����x�̉�����₷��
//    //int score_up[365][26]; // �����x�̑�����
//    //int contest[365]; // �R���e�X�g�̃^�C�v
//    //int last[26];
//
//    int d = 365;
//
//    class Contests {
//    public:
//        vector<int> body;
//        vector<vector<int>> pos;
//
//        Contests() {
//            body = vector<int>(d);
//            pos = vector<vector<int>>(26, vector<int>());
//        }
//    };
//
//    // �X�R�A���v�Z����
//    int CalcScore(vector<int>& score_down, vector<vector<int>>& score_up, vector<int>& contest) {
//        int score = 0;
//        vector<int> last(26, -1);
//        rep(i, d) {
//            int type = contest[i] - 1;
//            // �����x�̑���
//            score += score_up[i][type];
//            last[type] = i;
//            // ���Ԃɂ�閞���x�̒ቺ
//            rep(j, 26) {
//                score -= score_down[j] * (i - last[j]);
//            }
//        }
//        return score;
//    }
//
//    // �X�R�A�̍����v�Z����
//    int CalcScoreDiff(vector<int>& contest, vector<int>& score_down, vector<vector<int>>& score_up, int first, int second, int score) {
//        int tmp = contest[first];
//        contest[first] = second;
//        // �O��̏ꏊ�����߂�
//        int new_score = CalcScore(score_down, score_up, contest);
//        contest[first] = tmp;
//        return new_score - score;
//    }
//
//    // �R�o��@����Ȃ�
//    int NotHillClimbing(vector<int>& contest, vector<int>& score_down, vector<vector<int>>& score_up) {
//        // �����X�R�A�̌v�Z
//        int score = 0;
//        score = CalcScore(score_down, score_up, contest);
//
//        int cnt = 0;
//        while (cnt++ < 5 * 30) {
//            for (int head = 1; head < d; ++head) {
//                // �ύX��������_����
//                int type = rand() % 26 + 1;
//                int score_diff = CalcScoreDiff(contest, score_down, score_up, head, type, score);
//
//                // �悭�Ȃ���
//                if (score_diff > 0) {
//                    score += score_diff;
//                    contest[head] = type;
//                }
//            }
//        }
//
//        return true;
//    }
//
//    // �����̃R���e�X�g��ݒ�
//    void InitializeContests(Contests& contests, vector<int>& score_down) {
//        //// �R���e�X�g���ϓ��Ȑ����ׂ�
//        //vector<pair<int, int>> s_down(26);
//        //rep(i, 26) {
//        //    s_down[i] = { score_down[i], i };
//        //}
//        //sort(allof(s_down), greater<pair<int, int>>());
//        //// �R�X�g�̌������傫���z�قǗʂ𑽂�����
//
//        // ���̓����_����...
//        rep(i, d) {
//            int type = rand() % 26 + 1;
//            contests.body[i] = type;
//            contests.pos[type].emplace_back(i);
//        }
//    }
//}
//
//int main() {
//    srand((unsigned)time(NULL));
//
//    cin >> d;
//    vector<int> score_down = inp(26);
//    vector<vector<int>> score_up = inp(d, 26);
//    Contests contest;
//
//    // �Ƃ肠�����R�o��@����Ă݂�
//    InitializeContests(contest, score_down);
//
//    NotHillClimbing(contest, score_down, score_up);
//
//    Cout(contest, "\n");
//
//    return 0;
//}
