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
#include <stdio.h>
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

//using namespace std;

#define Rep(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,b) Rep(i,0,b)
#define allof(a) (a).begin(), (a).end()

using ll =  long long;

constexpr int inf = 1e9 + 7;
constexpr ll infll = 1ll << 60ll;
constexpr ll mod = 1e9 + 7;
// 0~3までは右左下上 4~7までは斜め
constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };

template<typename T> void chmax(T& a, T b) { a = std::max(a, b); }
template<typename T> void chmin(T& a, T b) { a = std::min(a, b); }
template<typename T> void chadd(T& a, T b) { a = a + b; }

namespace {  // 名前なし名前空間
	// Bit演算を楽にするライブラリ
	// @author tada
	class Bit {
	public:
		// コンストラクタでサイズ数
		Bit(int length) {
			length_ = length;
			bit_ = -1; // while(bit.next()) をされるのを想定
		}

		// 一つ先の値に移動する もう次に進めないならばfalseを返す
		bool Next() {
			if (++bit_ >= (1 << length_)) return false;
			return true;
		}

		// Bit操作 指定したインデックスを変更する
		void Change(int i, int value = 1) {
			if (value == 1) bit_ |= (1 << i);
			else bit_ &= ~(1 << i);
		}

		// 指定したインデックスが1かどうか
		bool IsSelected(int i) {
			return bit_ & (1 << i);
		}

		// 1の個数を返す 引数で範囲 [l, r)
		int GetSelectedNum(int l, int r) {
			int res = 0;
			for (int i = l; i < r; ++i) {
				if (IsSelected(i)) ++res;
			}
			return res;
		}

		// ビット列をint型で返す
		int GetBit() {
			return bit_;
		}

		// ビット長を返す
		int GetLength() {
			return length_;
		}

	private:
		int bit_;
		int length_;
	};
}


// ABC142E https://atcoder.jp/contests/abc142/tasks/abc142_e
/*
int main() {

	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(m), b(m);
	std::vector<std::vector<int>> c;
	rep(i, m) {
		std::cin >> a[i] >> b[i];
		std::vector<int> tmp(b[i]);
		rep(j, b[i]) std::cin >> tmp[j];
		rep(j, b[i]) --tmp[j];
		c.push_back(tmp);
	}

	// bitで宝箱が空いているかいないかを選択

	// dp[i][bit] := i番目までの鍵を任意に購入してbit状態の時の必要な最低費用
	std::vector<std::vector<int>> dp(m + 1, std::vector<int>((1 << n), inf));

	rep(i, m) {
		dp[i][0] = 0;
	}

	rep(i, m) {
		Bit bit(n);
		while (bit.Next()) {
			// 現在のbitの状態でi番目の鍵を購入するかしないか
			if (dp[i][bit.GetBit()] == inf) continue;

			// 購入する
			// 変化後のビット
			Bit new_bit = bit;
			rep(j, b[i]) {
				new_bit.Change(c[i][j], 1);
			}
			chmin(dp[i + 1][new_bit.GetBit()], dp[i][bit.GetBit()] + a[i]);

			// 購入しない
			chmin(dp[i + 1][bit.GetBit()], dp[i][bit.GetBit()]);
		}
	}

	// すべてそろった状態での最小費用
	int ans = dp[m][(1 << n) - 1];
	if (ans == inf) ans = -1;

	std::cout << ans << std::endl;

	return 0;
}
*/