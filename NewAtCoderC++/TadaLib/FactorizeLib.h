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

using pint = std::pair<int, int>;
using pll = std::pair<ll, ll>;

namespace {  // 名前なし名前空間
	// 素因数分解 O(√N)
	template <typename T>
	std::vector<T> Factorize2Vector(T x) {
		if (x <= 1) return std::vector<T>();
		std::vector<T> r; T x0 = x;
		while (x % 2 == 0)
			x /= 2, r.push_back(2);
		for (long long f = 3; f * f <= x0; f += 2)
			while (x % f == 0)
				x /= f, r.push_back(f);
		if (x > 1) r.push_back(x);
		return r;
	}
	template<typename T>
	std::map<T, T> Factorize2Map(T x) {
		if (x <= 1) return std::map<T, T>();
		std::map<T, T> mp;
		for (T i = 2; i * i <= x; ++i) {
			while (x % i == 0) {
				x /= i;
				mp[i]++;
			}
		}
		if (x != 1) {
			mp[x]++;
		}
		return mp;
	}

	// 素因数分解 pair.firstで素数、pair.secondで対応する指数
	std::vector<std::pair<long long, long long> > prime_factorize(long long n) {
		std::vector<std::pair<long long, long long> > res;
		for (long long p = 2; p * p <= n; ++p) {
			if (n % p != 0) continue;
			int num = 0;
			while (n % p == 0) { ++num; n /= p; }
			res.push_back(std::make_pair(p, num));
		}
		if (n != 1) res.push_back(std::make_pair(n, 1));
		return res;
	}

	const int MAX = 2100000;

	//二項係数を求める前処理 テーブルを作る　O(n)
	// facは階乗
	long long fac[MAX], finv[MAX], inv[MAX];
	void COMinit() {
		fac[0] = fac[1] = 1;
		finv[0] = finv[1] = 1;
		inv[1] = 1;
		for (int i = 2; i < MAX; i++) {
			fac[i] = fac[i - 1] * i % mod;
			inv[i] = mod - inv[mod % i] * (mod / i) % mod;
			finv[i] = finv[i - 1] * inv[i] % mod;
		}
	}

	// 二項係数計算
	ll COM(int n, int k) {
		if (n < k) return 0;
		if (n < 0 || k < 0) return 0;
		return fac[n] * (finv[k] * finv[n - k] % mod) % mod;
	}
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