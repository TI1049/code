#include <bits/stdc++.h>
using namespace std;

int main() {
	int _T; cin >> _T;
	for (int i = 1; i <= _T; ++i) {
		printf("Case #%d: ", i);
		int r, b;
		scanf("%d%d", &r, &b);
		if (r < 2) puts("0/1");
		else {
			int A = r * (r - 1);
			int B = (r + b) * (r + b - 1);
			int _g = __gcd(A, B);
			A /= _g;
			B /= _g;
			printf("%d/%d\n", A, B);
		}
	}
	return 0;
}
