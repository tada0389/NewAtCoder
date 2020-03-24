#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <map>
#include <set>
#include <sstream>
#include <stdio.h>
#include <cstdio>
#include <cstring>

using namespace std;

#define Rep(i,a,b) for(int i = a; i < b; i++)
#define rep(i,b) Rep(i,0,b)
#define rrep(i,a) for(int i = a; i >= 0; i--)
#define allof(a) (a).begin(), (a).end()

typedef long long ll;
const int inf = 1e9 + 7;
const ll infll = 1ll << 60ll;
const ll mod = 1e9 + 7;
// 0~3までは右左下上 4~7までは斜め
constexpr int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
constexpr int dy[] = { 0, -1, 0, 1, 1, -1, -1, 1 };

/*
// 最大公約数
ll gcd(ll a, ll b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}
// 最小公約数
long lcm(long a, long b) {
	return a / gcd(a, b) * b;
}*/
/*
#define MAX_V 200000
vector<pair<ll, ll>> G[MAX_V];
// ダイクストラ法
vector<ll> dijkstra(ll start) {
	vector<ll> dist(MAX_V, infll);
	dist[start] = 0; // dist[i] := start->iまでの最短距離
	priority_queue < pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> que;
	que.push({ 0, start });
	while (!que.empty()) {
		ll cost, u; // 今までにかかった時間　現在の頂点
		cost = que.top().first, u = que.top().second;
		que.pop();
		if (dist[u] < cost) continue;
		for (auto tmp : G[u]) {
			ll v = tmp.first, time = tmp.second; // 隣接する頂点、その頂点まで行く時間
			if (dist[v] > dist[u] + time) {
				dist[v] = dist[u] + time;
				que.push({ dist[v], v });
			}
		}
	}
	return dist;
}
int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n, m, t;
	cin >> n >> m >> t;
	vector<ll> A(n);
	rep(i, n) cin >> A[i];
	vector<ll> a(m), b(m), c(m);
	rep(i, m) {
		cin >> a[i] >> b[i] >> c[i];
		a[i]--, b[i]--;
		G[a[i]].push_back({ b[i],c[i] });
	}
	auto dist1 = dijkstra(0); // 1からi(1~n)まで行く最短距離
	rep(i, MAX_V) {
		G[i].clear(); // すべて削除
	}
	rep(i, m) {
		G[b[i]].push_back({ a[i], c[i] }); // 向きを逆にして入れる
	}
	auto dist2 = dijkstra(0);
	ll ans = 0;
	rep(i, n) {
		if (dist1[i] + dist2[i] <= t) {
			ll d = (t - dist1[i] - dist2[i]) * A[i];
			ans = max(ans, d);
		}
	}
	cout << ans << endl;
	return 0;
}*/