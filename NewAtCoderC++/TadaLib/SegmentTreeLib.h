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

	template <typename T> void Cout(T& x, char end = '\n') { std::cout << x << end; }
	template <typename T> void Cout(std::vector<T>& x, char sep = ' ', char end = '\n') { for (std::size_t i = 0, sz = x.size(); i < sz; i++) { std::cout << x[i] << (i == sz - 1 ? end : sep); } }


	// �W�����o��
	struct inp {
		size_t sz;
		inp(size_t _sz = 1) : sz(_sz) {}
		template <typename T> operator T () const { T a; std::cin >> a; return a; }
		template <typename T> operator std::vector<T>() const { vector<T> a(sz); for (std::size_t i = 0; i < sz; i++) std::cin >> a[i]; return a; }
		template <typename T, typename U> operator std::pair<T, U>() const { T f; U s; std::cin >> f >> s; return std::pair<T, U>(f, s); }
	};

	inp inp1; // input one

	// �Z�O�����g�c���[�̃��C�u����
	template<typename T>
	class SegmentTree {
	public:
		// _n:�K�v�T�C�Y, _def:�����l���P�ʌ�, _operation:�N�G���֐�,
		// _update:�X�V�֐�
		SegmentTree(size_t _n, T _def, std::function<T(T, T)> _operation,
			std::function<T(T, T)> _update)
			: def(_def), operation(_operation), update(_update) {
			n = 1;
			while (n < _n) {
				n *= 2;
			}
			data = std::vector<T>(2 * n - 1, def);
		}

		// �ꏊi(0-indexed)�̒l��x�ōX�V
		void change(int i, T x) {
			i += n - 1;
			data[i] = update(data[i], x);
			while (i > 0) {
				i = (i - 1) / 2;
				data[i] = operation(data[i * 2 + 1], data[i * 2 + 2]);
			}
		}

		// [a, b)�̋�ԃN�G�������s
		T query(int a, int b) {
			return _query(a, b, 0, 0, n);
		}

		// �Y���ŃA�N�Z�X
		T operator[](int i) {
			return data[i + n - 1];
		}
	private:
		int n;                       // �t�̐�
		std::vector<T> data;              // �f�[�^���i�[����vector
		T def;                       // �����l���P�ʌ�
		std::function<T(T, T)> operation; // ��ԃN�G���Ŏg������
		std::function<T(T, T)> update;    // �_�X�V�Ŏg������

		// ���[a,b)�̑��a�B�m�[�hk=[l,r)�ɒ��ڂ��Ă���B
		T _query(int a, int b, int k, int l, int r) {
			if (r <= a || b <= l) return def; // �������Ȃ�
			if (a <= l && r <= b)
				return data[k]; // a,l,r,b�̏��Ŋ��S�Ɋ܂܂��
			else {
				T c1 = _query(a, b, 2 * k + 1, l, (l + r) / 2); // ���̎q
				T c2 = _query(a, b, 2 * k + 2, (l + r) / 2, r); // �E�̎q
				return operation(c1, c2);
			}
		}
	};
}


// https://atcoder.jp/contests/exawizards2019/tasks/exawizards2019_c
int main() {

	int n, q;
	std::cin >> n >> q;
	std::vector<int> com(q), x(q), y(q);
	rep(i, q) std::cin >> com[i] >> x[i] >> y[i];

	//SegmentTree<int> seg(n, inf,[](int a, int b)->int {return std::min(a, b); }, [](int a, int b)->int {return b; });

	//for (int i = 0; i < q; ++i) {
	//	if(com[i] == 0) seg.change(x[i], y[i]);
	//	else std::cout << seg.query(x[i], y[i] + 1) << std::endl;
	//}

	SegmentTree<int> seg(n, 0, [](int a, int b)->int {return a + b; }, [](int a, int b)->int {return a + b; });

	for (int i = 0; i < q; ++i) {
		if (com[i] == 0) seg.change(x[i] - 1, y[i]);
		else std::cout << seg.query(x[i] - 1, y[i]) << std::endl;
	}
}

// https://atcoder.jp/contests/abc157/tasks/abc157_e
//int main() {
//
//	int n = inp1;
//	string s = inp1;
//	int q = inp1;
//
//	auto f = [](int a, int b)->int {
//		return a + b;
//	};
//	auto g = [](int a, int b)->int {
//		return a + b;
//	};
//
//	// ��΃Z�O��
//	vector<SegmentTree<int>> segs(26, SegmentTree<int>(n, 0,
//		//[](int a, int b)->int {return a + b; }, // update 
//		//[](int a, int b)->int {return a + b; } // return
//		f,
//		g
//		));
//
//	// ������
//	rep(i, s.size()) {
//		segs[(s[i] - 'a')].change(i, 1);
//	}
//
//	// �����̎��
//	rep(query, q) {
//		int b = inp1;
//		if (b == 1) { // ������ύX
//			int i = inp1;
//			char c = inp1;
//			segs[(s[i - 1] - 'a')].change(i - 1, -1);
//			segs[(c - 'a')].change(i - 1, 1);
//			s[i - 1] = c;
//		}
//		else { // ����Ԃ�
//			int l, r;
//			cin >> l >> r;
//			int res = 0;
//			rep(i, 26) {
//				if (segs[i].query(l - 1, r) > 0) ++res;
//			}
//			Cout(res);
//		}
//	}
//
//	return 0;
//}