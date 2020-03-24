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

using namespace std;

#define Rep(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,b) Rep(i,0,b)
#define allof(a) (a).begin(), (a).end()

#define Yes(q) ((q) ? "Yes" : "No")
#define YES(q) ((q) ? "YES" : "NO")
#define Possible(q) ((q) ? "Possible" : "Impossible")
#define POSSIBLE(q) ((q) ? "POSSIBLE" : "IMPOSSIBLE")

using ll =  long long;

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
	template<typename T> T gcd(T a, T b) { if (a < b) std::swap(a, b); while (b) std::swap(a %= b, b); return a; }
	template<typename T> T lcm(const T a, const T b) { return a / gcd(a, b) * b; }

	void Cout(long long x, const char* end = "\n") { std::cout << x << end; }
	template <typename T> void Cout(const T& x, const char* end = "\n") { std::cout << x << end; }
	template <typename T> void Cout(const std::vector<T>& x, const char* sep = " ", const char* end = "\n") {
		for (std::size_t i = 0, sz = x.size(); i < sz; i++) {
			std::cout << x[i] << (i == sz - 1 ? end : sep);
		}
	}

	// �W�����o��
	struct inp {
		size_t sz;
		inp(size_t _sz = 1) : sz(_sz) {}
		template <typename T> operator T () const { T a; std::cin >> a; return a; }
		template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
		template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
	};

	inp inp1; // input one

	// �x���]���Z�O�����g�c���[�̃��C�u����
	template<typename T>
	struct LazySegmentTree {
	public:
		// a:�����z��, def:�����l���P�ʌ�, operation:�N�G���֐�,
		// update:�X�V�֐�
		LazySegmentTree(vector<T> a, T def, std::function<T(T, T)> operation,
			std::function<T(T, T)> update)
			: def_(def) { //, operation_(operation), update_(update) {

			n_ = 1;

			size_t sz = a.size();
			while (n_ < sz) n_ *= 2;

			node_.resize(2 * n_, def_);
			lazy_.resize(2 * n_, def_);

			for (size_t i = 0; i < sz; ++i) node_[i + n_ - 1] = a[i];
			for (int i = n_ - 2; i >= 0; --i) node_[i] = node_[i * 2 + 1] + node_[i * 2 + 2];
		}

		// k�Ԗڂ̃m�[�h�ɂ��Ēx���]������ �����̃m�[�h�̓Y�����C�m�[�h���w���͈͂�n��
		void eval(int k, int l, int r) {
			if (lazy_[k] != 0) {
				node_[k] += lazy_[k]; // �����̃m�[�h�֓`�d
				if (r - l > 1) { // �q�m�[�h�̒x���z��ɒl��`�d
					// �q�m�[�h�͐e�m�[�h��1/2�͈̔�
					lazy_[k * 2 + 1] += lazy_[k] / 2;
					lazy_[k * 2 + 2] += lazy_[k] / 2;
				}
				lazy_[k] = 0; // �����̃m�[�h�̒x���z�����ɂ���
			}
		}

		void add(int a, int b, T x, int k = 0, int l = 0, int r = -1) {
			if (r < 0) r = n_;

			// k�Ԗڂ̃m�[�h�ɑ΂��Ēx���]�����s��
			eval(k, l, r);
			// �͈͊O�Ȃ牽�����Ȃ�
			if (r <= a || b <= l) return;

			// ���S�ɔ핢���Ă���Ȃ�΁C�x���z��ɒl����ꂽ��ɕ]��
			if (a <= l && r <= b) {
				lazy_[k] += (r - l) * x;
				eval(k, l, r);
			}
			else { // �����łȂ���΁C�q�m�[�h�̒l���ċA�I�Ɍv�Z���āC�v�Z�ς݂̒l��������Ă���
				add(a, b, x, k * 2 + 1, l, (l + r) / 2);
				add(a, b, x, k * 2 + 2, (l + r) / 2, r);
				node_[k] = node_[k * 2 + 1] + node_[k * 2 + 2];
			}
		}

		T getsum(int a, int b, int k = 0, int l = 0, int r = -1) {
			if (r < 0) r = n_;
			// �֐����Ăяo���ꂽ��]��
			eval(k, l, r);
			if (r <= a || b <= l) return 0;
			if (a <= l && r <= b) return node_[k];
			T lv = getsum(a, b, k * 2 + 1, l, (l + r) / 2);
			T rv = getsum(a, b, k * 2 + 2, (l + r) / 2, r);
			return lv + rv;
		}
	private:
		int n_;
		std::vector<T> node_;
		std::vector<T> lazy_;
		T def_;                       // �����l���P�ʌ�
		//std::function<T(T, T)> operation_; // ��ԃN�G���Ŏg������
		//std::function<T(T, T)> update_;    // �_�X�V�Ŏg������

	};
}


// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja
int main() {
	int n = inp1;
	int q = inp1;

	std::vector<int> a(n, 0);

	LazySegmentTree<int> segment_tree(a, 0, [](int a, int b)->int {return a + b; }, [](int a, int b)->int {return a + b; });

	rep(i, q) {
		int b = inp1;
		if (b == 0) { // add(s, t, x)
			int s, t, x;
			cin >> s >> t >> x;
			segment_tree.add(s - 1, t, x);
		}
		else { // getSum(s, t)
			int s, t;
			cin >> s >> t;
			Cout(segment_tree.getsum(s - 1, t));
		}
	}
	return 0;
}