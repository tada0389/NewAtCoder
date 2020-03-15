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
// 0~3�܂ł͉E������ 4~7�܂ł͎΂�
constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };

template<typename T> void chmax(T& a, T b) { a = std::max(a, b); }
template<typename T> void chmin(T& a, T b) { a = std::min(a, b); }
template<typename T> void chadd(T& a, T b) { a = a + b; }

namespace {  // ���O�Ȃ����O���
	// Bit���Z���y�ɂ��郉�C�u����
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

	// bit�ŕ󔠂��󂢂Ă��邩���Ȃ�����I��

	// dp[i][bit] := i�Ԗڂ܂ł̌���C�ӂɍw������bit��Ԃ̎��̕K�v�ȍŒ��p
	std::vector<std::vector<int>> dp(m + 1, std::vector<int>((1 << n), inf));

	rep(i, m) {
		dp[i][0] = 0;
	}

	rep(i, m) {
		Bit bit(n);
		while (bit.Next()) {
			// ���݂�bit�̏�Ԃ�i�Ԗڂ̌����w�����邩���Ȃ���
			if (dp[i][bit.GetBit()] == inf) continue;

			// �w������
			// �ω���̃r�b�g
			Bit new_bit = bit;
			rep(j, b[i]) {
				new_bit.Change(c[i][j], 1);
			}
			chmin(dp[i + 1][new_bit.GetBit()], dp[i][bit.GetBit()] + a[i]);

			// �w�����Ȃ�
			chmin(dp[i + 1][bit.GetBit()], dp[i][bit.GetBit()]);
		}
	}

	// ���ׂĂ��������Ԃł̍ŏ���p
	int ans = dp[m][(1 << n) - 1];
	if (ans == inf) ans = -1;

	std::cout << ans << std::endl;

	return 0;
}
*/