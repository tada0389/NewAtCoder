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

using pint = std::pair<int, int>;
using pll = std::pair<ll, ll>;

namespace {  // 名前なし名前空間
	ll powll(ll a, ll n) {
		ll result = 1;
		ll base = a;
		ll mask = 1;
		while (mask <= n) {
			if (n & mask) (result *= base) %= mod;
			mask <<= 1;
			(base *= base) %= mod;
		}
		return result;
	}

	template<int MOD> struct Fp {
		long long val;
		constexpr Fp(long long v = 0) noexcept : val(v% MOD) {
			if (val < 0) val += MOD;
		}
		constexpr int getmod() { return MOD; }
		constexpr Fp operator - () const noexcept {
			return val ? MOD - val : 0;
		}
		constexpr Fp operator + (const Fp& r) const noexcept { return Fp(*this) += r; }
		constexpr Fp operator - (const Fp& r) const noexcept { return Fp(*this) -= r; }
		constexpr Fp operator * (const Fp& r) const noexcept { return Fp(*this) *= r; }
		constexpr Fp operator / (const Fp& r) const noexcept { return Fp(*this) /= r; }
		constexpr Fp& operator += (const Fp& r) noexcept {
			val += r.val;
			if (val >= MOD) val -= MOD;
			return *this;
		}
		constexpr Fp& operator -= (const Fp& r) noexcept {
			val -= r.val;
			if (val < 0) val += MOD;
			return *this;
		}
		constexpr Fp& operator *= (const Fp& r) noexcept {
			val = val * r.val % MOD;
			return *this;
		}
		constexpr Fp& operator /= (const Fp& r) noexcept {
			long long a = r.val, b = MOD, u = 1, v = 0;
			while (b) {
				long long t = a / b;
				a -= t * b; std::swap(a, b);
				u -= t * v; std::swap(u, v);
			}
			val = val * u % MOD;
			if (val < 0) val += MOD;
			return *this;
		}
		constexpr bool operator == (const Fp& r) const noexcept {
			return this->val == r.val;
		}
		constexpr bool operator != (const Fp& r) const noexcept {
			return this->val != r.val;
		}
		friend constexpr std::ostream& operator << (std::ostream& os, const Fp<MOD>& x) noexcept {
			return os << x.val;
		}
		friend constexpr Fp<MOD> modpow(const Fp<MOD>& a, long long n) noexcept {
			if (n == 0) return 1;
			auto t = modpow(a, n / 2);
			t = t * t;
			if (n & 1) t = t * a;
			return t;
		}
	};
	using mint = Fp<mod>;
}


/* 参考 */
/*
int main() {

	ll n;
	std::cin >> n;
	std::vector<ll> a(n);
	rep(i, n) std::cin >> a[i];

	// xを構成する要素
	std::map<ll, ll> mp;

	rep(i, n) {
		auto mp2 = Factorize2Map(a[i]);
		// 素因数を取得できた
		for (auto v : mp2) {
			mp[v.first] = std::max(mp[v.first], v.second);
		}
	}

	mint ans = 0;

	mint lcm = 1;
	for (auto v : mp) {
		mint tmp = Powll(v.first, v.second);
		lcm *= tmp;
	}

	rep(i, n) {
		ans += lcm / mint(a[i]);
	}

	std::cout << ans << std::endl;

	return 0;
}
*/