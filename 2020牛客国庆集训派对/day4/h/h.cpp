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
constexpr int N = 2e5 + 10; 
int n, q, c[N];
ll sum[N];

vector <vector<int>> G;
set <int> se[N];

int fa[N], deep[N], dis[N], sze[N], son[N], top[N], in[N], fin[N];

void dfs(int u) {
	sze[u] = 1;
	son[u] = 0;
	for (auto &v : G[u]) {
		if (v == fa[u]) continue;
		fa[v] = u;
		deep[v] = deep[u] + 1;
		dis[v] = dis[u] + 1;
		dfs(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;
	}
}

void gettop(int u, int tp) {
	in[u] = ++*in;
	fin[*in] = u;
	top[u] = tp;
	if (son[u]) gettop(son[u], tp);
	for (auto &v : G[u]) {
		if (v == fa[u] || v == son[u]) continue;
		gettop(v, v);
	}
}

int querylca(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;
}

int querydis(int u, int v) { return dis[u] + dis[v] - 2 * dis[querylca(u, v)]; }

void add(int col, int x) {
    if (SZ(se[col]) == 1) {
		auto pos = se[col].begin();
		sum[col] += querydis(x, fin[*pos]) * 2;
	} else if (SZ(se[col]) > 1) {
		auto nx = se[col].upper_bound(in[x]);
		if (nx == se[col].end()) nx = se[col].begin();
		auto pre = prev(nx);
		if (nx == se[col].begin()) pre = prev(se[col].end());
		sum[col] -= querydis(fin[*nx], fin[*pre]);
		sum[col] += querydis(x, fin[*nx]);
		sum[col] += querydis(x, fin[*pre]);
	}
	se[col].insert(in[x]);
}

void del(int col, int x) {
	if (SZ(se[col]) <= 2) {
		sum[col] = 0;
	} else {
		auto pos = se[col].lower_bound(in[x]);
		auto nx = next(pos);
		auto pre = prev(pos);
		if (pos == se[col].begin()) pre = prev(se[col].end());
		if (nx == se[col].end()) nx = se[col].begin();
		sum[col] -= querydis(x, fin[*nx]);
		sum[col] -= querydis(x, fin[*pre]);
		sum[col] += querydis(fin[*nx], fin[*pre]);
	}
	se[col].erase(in[x]);
}

void run() {
	rd(n);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i < n; ++i) {
		rd(u, v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	*in = 0;
	deep[1] = dis[1] = 0;
	fa[1] = 1;
	dfs(1);
	gettop(1, 1);
	memset(sum, 0, sizeof sum);
	for (int i = 1; i <= n; ++i) {
		rd(c[i]);
		add(c[i], i);
	}
	rd(q);
	char op[5];
	for (int i = 1, x, y; i <= q; ++i) {
		cin >> op;
		if (op[0] == 'U') {
			rd(x, y);
			if (c[x] == y) continue;
			del(c[x], x);
			c[x] = y;
			add(c[x], x);
		} else {
			rd(y);
			if (se[y].empty()) pt(-1);
			else pt(sum[y] / 2);
		}
	}
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
