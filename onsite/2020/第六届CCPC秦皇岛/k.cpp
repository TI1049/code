#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e6 + 10;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
#define SZ(x) (int(x.size()))
int n, m;
ll f[N], g[N];
vector <vector<int>> G;
vector <int> leaf;

#define dbg(x...) do { cout << #x << " -> "; err(x); } while (0)
void err() { cout << endl; }
template <class T, class... Ts> void err(const T& arg, const Ts&... args) {
	cout << arg << ' '; err(args...);
}

int fa[N], deep[N], son[N], sze[N], top[N], in[N];
void dfs(int u) {
	in[u] = ++*in;
	sze[u] = 1;
	son[u] = 0;
	for (auto &v : G[u]) {
		if (v == fa[u]) continue;
		fa[v] = u;
		deep[v] = deep[u] + 1;
		dfs(v);
		sze[u] += sze[v];
		if (!son[u] || sze[v] > sze[son[u]]) son[u] = v;
	}
	if (sze[u] == 1) leaf.push_back(u);
}

void gettop(int u, int tp) {
	top[u] = tp;
	if (!son[u]) return;
	gettop(son[u], tp);
	for (auto &v : G[u]) {
		if (v != son[u] && v != fa[u]) {
			gettop(v, v);
		}
	}
}

int query(int u, int v) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]]) {
			swap(u, v);
		}
		u = fa[top[u]];
	}
	if (deep[u] > deep[v]) swap(u, v);
	return u;
}

int dis(int u, int v) {
	return deep[u] + deep[v] - 2 * deep[query(u, v)]; 
}

ll calc() {
	ll Min[2] = { INFLL, INFLL };
	for (int i = 1; i <= m; ++i) f[i] = INFLL, g[i] = 0;
	f[0] = 0;
	g[0] = 0;
	for (int i = 1; i <= m; ++i) {
		int u = leaf[i - 1];
		g[i] = g[i - 1];
		int pre = -1;
		if (i > 1) pre = leaf[i - 2];
		f[i] = f[i - 1] + deep[u];
		if (pre != -1) {
			int _dis = dis(u, pre);
			g[i] += _dis; 
			f[i] = min(f[i], Min[0] + g[i]);
			f[i] = min(f[i], Min[1] + deep[u] + g[i]);
		}
		Min[0] = min(Min[0], f[i - 1] + deep[u] - g[i]);
		Min[1] = min(Min[1], f[i - 1] - g[i]);
	}
	return f[m];
}

void gao() {
	*in = 0;
	fa[1] = 1;
	deep[1] = 0;
	leaf.clear();
	dfs(1);
	gettop(1, 1);
	sort(leaf.begin(), leaf.end(), [&](int u, int v) {
		return in[u] < in[v];
	});
	m = SZ(leaf);
	ll res = calc();
		sort(leaf.begin(), leaf.end(), [&](int u, int v) {
		return in[u] > in[v];
	});
	res = min(res, calc());
	printf("%lld\n", res);
}

int main() {
	int _T; scanf("%d", &_T);
	for (int CAS = 1; CAS <= _T; ++CAS) {
		printf("Case #%d: ", CAS);
		scanf("%d", &n);
		G.clear(); G.resize(n + 1);
		for (int i = 2, fa; i <= n; ++i) {
			scanf("%d", &fa);
			G[fa].push_back(i);
		}
		gao();
	}
	return 0;
}
