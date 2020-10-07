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
constexpr int N = 1e5 + 10; 
int n, m; 
vector <vector<int>> G;

struct BIT_2D {
    struct BIT {
        ll a[N];
		void init() { memset(a, 0, sizeof a); }
        void add(int x, ll v) { for (; x < N; a[x] += v, x += x & -x); }
        ll ask(int x) { ll res = 0; for (; x > 0; res += a[x], x -= x & -x); return res; }
    }bit1, bit2;
	void init() { bit1.init(); bit2.init(); }
    ll ask(int x) { return (x + 1) * bit1.ask(x) - bit2.ask(x); }
    void add(int x, ll v) { bit1.add(x, v); bit2.add(x, x * v); }
    ll ask(int l, int r) { return ask(r) - ask(l - 1); }
    void add(int l, int r, ll v) { add(l, v); add(r + 1, -v); }
}bit;

struct HLD {
	int fa[N], deep[N], dis[N], sze[N], son[N], top[N], in[N], fin[N], out[N]; 
	void dfs(int u) {
		sze[u] = 1; son[u] = 0;
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
		in[u] = ++*in; fin[*in] = u;
		top[u] = tp;
		if (son[u]) gettop(son[u], tp);
		for (auto &v : G[u]) {
			if (v == son[u] || v == fa[u]) continue;
			gettop(v, v);
		}
		out[u] = *in;
	}
	void init(int rt) {
		fa[rt] = rt;
		dis[rt] = 0; 
		*in = 0;
		dfs(rt);
		gettop(rt, rt);
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
	void updatePath(int u, int v, ll x) {
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) swap(u, v);
			bit.add(in[top[u]], in[u], x);
			u = fa[top[u]];	
		}
		if (deep[u] > deep[v]) swap(u, v);
		bit.add(in[u], in[v], x);
	}	
	ll queryPath(int u, int v) {
		ll res = 0;
		while (top[u] != top[v]) {
			if (deep[top[u]] < deep[top[v]]) swap(u, v);
			res += bit.ask(in[top[u]], in[u]);
			u = fa[top[u]];
		}
		if (deep[u] > deep[v]) swap(u, v);
		res += bit.ask(in[u], in[v]);
		return res;
	}
	bool inSubTree(int u, int v) { return in[v] >= in[u] && in[v] <= out[u]; }
}hld;

struct E {
	int u, v, dis;
	E() {}
}e[N];

bool ok(int a1, int b1, int a2, int b2) {
	int t[] = {hld.querylca(a1, a2), hld.querylca(a1, b2), hld.querylca(b1, a2), hld.querylca(b1, b2)};
	sort(t, t + 4, [&](int a, int b) { return hld.deep[a] < hld.deep[b]; });
	int d[] = {hld.querylca(a1, b1), hld.querylca(a2, b2)};
	sort(d, d + 2, [&](int a, int b) { return hld.deep[a] < hld.deep[b]; });
	if (hld.deep[t[3]] >= hld.deep[t[2]] && hld.deep[t[2]] >= hld.deep[d[1]]) {
		int _a = t[2], _b = t[3];
		if (_a > _b) swap(_a, _b);
		if (a2 > b2) swap(a2, b2);
//		dbg(_a, _b);
		return _a == a2 && _b == b2;	
	} else {
		return false;
	}
}

void run() {
	rd(n, m);
	G.clear(); G.resize(n + 1);
	for (int i = 1, u, v; i < n; ++i) {
		rd(u, v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	bit.init();
	hld.init(1);
//	ok(1, 4, 2, 3);
//	dbg("vv");
//	return;
	for (int i = 1; i <= m; ++i) {
		rd(e[i].u, e[i].v);
		e[i].dis = hld.querydis(e[i].u, e[i].v) + 1;
//		dbg(e[i].u, e[i].v, e[i].dis);
	}
	sort(e + 1, e + 1 + m, [&](E a, E b) {
		return a.dis > b.dis;		
	});
//	return;
	int _ok = 1;
	for (int i = 1; i <= m; ++i) {
	//	dbg(i);
		int u = e[i].u, v = e[i].v, dis = e[i].dis;
		ll x = hld.queryPath(u, v);
		//dbg(u, v, x, dis);
		if (x == 0) {
			hld.updatePath(u, v, i);
		} else {
			if (x % dis == 0) {
				ll y = x / dis;
				if (!ok(e[y].u, e[y].v, u, v)) {
					_ok = 0;
					break;
				} else {
					hld.updatePath(u, v, -y);
					hld.updatePath(u, v, i);
				}
			} else {
				_ok = 0;
				break;
			}
		}
	}
	pt(_ok ? "Yes" : "No");
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
