#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int nextInt() { int x; cin >> x; return x; }
void rd() {}
template <class T, class... Ts> void rd(T& arg, Ts&... args) { cin >> arg; rd(args...); }
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 2e4 + 10; 
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n, m, k, id[N], fid[N]; 
pII a[N];
vector <vector<pII>> G;
ll f[1 << 19][19];

struct Dijkstra {
	struct node {
		int u; ll w;
		node(int u = 0, ll w = 0) : u(u), w(w) {}
		bool operator < (const node &other) const { return w > other.w; }		
	};
	ll dis[N]; bool used[N];
	void gao(int s) {
		for (int i = 1; i <= n; ++i) {
			dis[i] = INFLL;
			used[i] = 0;
		}
		priority_queue <node> pq;
		dis[s] = 0;
		pq.push(node(s, dis[s]));
		while (!pq.empty()) {
			int u = pq.top().u; pq.pop();
			if (used[u]) continue;
			used[u] = 1;
			for (auto &it : G[u]) {
				int v = it.fi, w = it.se;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					pq.push(node(v, dis[v]));
				}
			}
		}
	}
}dij[50];

void run() {
	rd(n, m, k);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v, w; i <= m; ++i) {
		rd(u, v, w);
		G[u].push_back(pII(v, w));
		G[v].push_back(pII(u, w));
	}
	memset(id, 0, sizeof id);
	for (int i = 0; i < k; ++i) {
		rd(a[i].fi, a[i].se);
		if (!id[a[i].fi]) id[a[i].fi] = ++*id, fid[*id] = a[i].fi;
		if (!id[a[i].se]) id[a[i].se] = ++*id, fid[*id] = a[i].se;
	}
	for (int i = 1; i <= *id; ++i) dij[i].gao(fid[i]);
	memset(f, 0x3f, sizeof f);
	for (int i = 0; i < k; ++i) {
		f[1 << i][i] = dij[id[a[i].fi]].dis[a[i].se];
	}
	for (int i = 1; i < 1 << k; ++i) {
		for (int j = 0; j < k; ++j) if ((i >> j) & 1 && f[i][j] < INF) {
			for (int o = 0; o < k; ++o) if (!((i >> o) & 1)){
				chmin(f[i | (1 << o)][o], f[i][j] + dij[id[a[o].fi]].dis[a[o].se] + dij[id[a[j].se]].dis[a[o].fi]);
			}
		}
	}
	ll res = INFLL;
	for (int i = 0; i < k; ++i) chmin(res, f[(1 << k) - 1][i]);
	if (res >= INFLL) res = -1;
	pt(res);
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	//nextInt();
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
