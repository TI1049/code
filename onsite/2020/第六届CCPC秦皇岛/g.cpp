#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, k;

ll calc(int x) {
	ll res = 1;
	for (int i = 1; i <= k; ++i) {
		res *= x;
		if (res > n) return n + 1;
	}
	return res;
}

ll gao(ll x, ll y) {
	return y / x;
}

int main() {
	int _T; scanf("%d", &_T);
	for (int CAS = 1; CAS <= _T; ++CAS) {
		printf("Case #%d: ", CAS);
		scanf("%d%d", &n, &k);
		if (k == 1) {
			printf("%d\n", n);
		} else {
			int limit = ceil(pow(n, 1.0 / k)) + 10;
			limit = min(limit, n);
			ll res = 0; 
			for (int i = 1; i <= limit; ++i) {
				ll l = calc(i);
				ll r = calc(i + 1);
				if (l < r) {
					res += gao(i, r - 1) - gao(i, l - 1);
				}
			}
			printf("%lld\n", res);
		}
	}
	return 0;
}
