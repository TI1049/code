#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
#define SZ(x) (int(x.size()))
const int N = 2e5 + 10;
int n, p;
int a[N], b[N];
int f[N]; 

void gao() {
	for (int i = 1; i <= n; ++i) f[i] = 0;
	vector <pII> vec;
	for (int i = 1; i <= n; ++i) {
		vec.push_back(pII(a[i], i));
		vec.push_back(pII(b[i], i));
	}
	sort(vec.begin(), vec.end());
	int res = 0, now = 0;
	int r = SZ(vec) - 1, l = SZ(vec) - 1;
	int m = SZ(vec) - 1;
	int MaxScore = 0;
	for (int i = 1; i <= n; ++i) {
		MaxScore = max(MaxScore, min({a[i], b[i]}));
	}
	for (int i = m; i >= 0; --i) {
		int Max = vec[i].fi;
		if (Max < MaxScore) break;
		ll pMax = 1ll * p * Max;
		while (l >= 0 && 1ll * vec[l].fi * 100 >= pMax) {
			int id = vec[l].se;
			++f[id];
			if (f[id] == 1) ++now;
			--l;
		}
		while (r >= 0 && vec[r].fi > Max) {
			int id = vec[r].se;
			--f[id];
			if (f[id] == 0) --now;
			--r;
		}
		res = max(res, now);
	}
	printf("%d\n", res);
}

int main() {
	int _T; scanf("%d", &_T);
	for (int CAS = 1; CAS <= _T; ++CAS) {
		printf("Case #%d: ", CAS);
		scanf("%d%d", &n, &p);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", a + i, b + i);
		}		
		gao();
	}
	return 0;
}
