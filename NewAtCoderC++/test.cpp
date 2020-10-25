#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <numeric>
#include <iomanip>
#include <stack>
#include <tuple>

using namespace std;

using ll = long long;

template<class T>bool chmax(T& a, const T& b) { if (a < b) { a = b; return 1; } return 0; }
template<class T>bool chmin(T& a, const T& b) { if (b < a) { a = b; return 1; } return 0; }

const int inf = (1 << 30) - 1;

int main() {

    vector<int> ans;

    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) break;

        vector<int> h(n);
        vector<int> w(m);
        for (int i = 0; i < n; ++i) cin >> h[i];
        for (int j = 0; j < m; ++j) cin >> w[j];

        // ³•ûŒ`‚Ì”‚ğŒvZ‚·‚é

        // n, m <= 1500

        constexpr int kMaxLength = 1500001;
        vector<int> cnt_h(kMaxLength, 0);
        vector<int> cnt_w(kMaxLength, 0);

        for (int i = 0; i < n; ++i) {
            int len = 0;
            for (int j = i; j < n; ++j) {
                len += h[j];
                ++cnt_h[len];
            }
        }

        for (int i = 0; i < m; ++i) {
            int len = 0;
            for (int j = i; j < m; ++j) {
                len += w[j];
                ++cnt_w[len];
            }
        }

        int res = 0;
        for (int i = 0; i < kMaxLength; ++i) {
            //cout << cnt_h[i] << " " << cnt_w[i] << endl;
            res += cnt_h[i] * cnt_w[i];
        }

        ans.emplace_back(res);
    }

    for (auto res : ans) cout << res << endl;
}