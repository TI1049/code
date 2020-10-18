#include <bits/stdc++.h>
using namespace std;
#define SZ(x) (int(x.size()))

const int N = 3e5 + 10;
int n, m;
vector <vector<int>> G, T;

struct UFS {
	int fa[N], sze[N];
	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = 0;
			sze[i] = 1;
		}
	}
	int find(int u) {
		return fa[u] ? fa[u] = find(fa[u]) : u;
	}
	void merge(int u, int v) {
		int fu = find(u), fv = find(v);
		if (fu != fv) {
			if (sze[fu] > sze[fv]) {
				swap(fu, fv);
			}
			fa[fv] = fu;
			sze[fu] += sze[fv];
		}
	}
}ufs;

int main() {
	int _T; scanf("%d", &_T);
	for (int CAS = 1; CAS <= _T; ++CAS) {
		printf("Case #%d: ", CAS);
		scanf("%d%d", &n, &m);
		G.clear(); G.resize(n + 1);
		ufs.init(n);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
			ufs.merge(u, v);
		}
		T.clear(); T.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			T[ufs.find(i)].push_back(i);
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			if (!T[i].empty()) {
				int E = 0, V = SZ(T[i]);
				for (auto &it : T[i]) {
					E += SZ(G[it]);
				}
				E /= 2;
				if (E - V > 0) res += E - V;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
