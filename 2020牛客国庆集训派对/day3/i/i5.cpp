#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 5e5 + 10; 
constexpr int M = 1300;
constexpr int mod = 998244353;
int n, f[M], g[N];

// g[i] 表示 i 的划分数
void gao() { 
	f[1] = 1, f[2] = 2, f[3] = 5, f[4] = 7;
	for (int i = 5; i < M; ++i) f[i] = 3 + 2 * f[i - 2] - f[i - 4];
    g[0] = 1;
    for (int i = 1; i <= n; ++i) {
		ll sum[4] = {0}, now = 0;
		int j = 1;
		for (; f[j + 3] <= i; j += 4) {
			sum[0] += g[i - f[j]];
			sum[1] += g[i - f[j + 1]];
			sum[2] -= g[i - f[j + 2]];
			sum[3] -= g[i - f[j + 3]];
		}
		now = (sum[0] + sum[1] + sum[2] + sum[3]) % mod;
		for (; f[j] <= i; ++j) {
			if ((j + 1) >> 1 & 1) {
				now += g[i - f[j]];
			} else {
				now -= g[i - f[j]];
			}
		}
		now = (now + mod) % mod;
		g[i] = now;
    }
}

int main() {
	cin >> n;
	gao();
	cout << g[n - 1] << endl;
	return 0;
}
