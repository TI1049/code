#include <bits/stdc++.h>
using namespace std;
using db = long double;
using pII = pair <int, int>;
#define fi first
#define se second
constexpr int N = 1e5 + 10; 
constexpr db eps = 1e-11;
int n;
pII a[N];

int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

bool ok(db x) {
	db st = 0;
	for (int i = 1; i <= n; ++i) {
		st = max(st, (db)1.0 * a[i].fi);
		db ed = st + x;
		if (sgn(ed - a[i].se) > 0) return false;	
		st = ed;
	}
	return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].fi, &a[i].se);
	}
	sort(a + 1, a + 1 + n, [&](pII a, pII b){
		if (a.fi == b.fi)
			return a.se < b.se;
		return a.fi < b.fi;
	});
	db l = 0, r = a[n].se;
	while (r - l > eps) {
		db mid = (l + r) / 2;
		if (ok(mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	db Min = 0x3f3f3f3f;
	int p, q;
	for (int i = 1; i <= N; ++i) {
		for (auto &j : {floor(l * i), ceil(l * i)}) {
			if (fabs(j * 1.0 / i - l) < Min) {
				p = j;
				q = i;
				Min = fabs(j * 1.0 / i - l);
			}
		}
	}
	cout << p << "/" << q << endl;
	return 0;
}

