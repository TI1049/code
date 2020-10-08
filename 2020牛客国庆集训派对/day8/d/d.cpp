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
constexpr int N = 1e2 + 10; 
int n, P, A, C, M;
int f[2][40][40][40][40], g[2][40][40][40][40];

struct E {
	int p, a, c, m, g;
	E() {}
	void scan() {
		rd(p, a, c, m, g);
	}
}e[N];

void run() {
	rd(n);
	for (int i = 1; i <= n; ++i) e[i].scan();
	rd(P, A, C, M);
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	pII ran[2] = {pII(1, min(18, n)), pII(19, n)};
	for (int o = 0; o < 2; ++o) {
		int l = ran[o].fi, r = ran[o].se;
		if (l > r) continue;
		for (int S = 1; S < 1 << 18; ++S) {
			int _P = 0, _A = 0, _C = 0, _M = 0, _G = 0;
			for (int i = 0; i < r - l + 1; ++i) {
				if ((S >> i) & 1) {
					int _i = l + i;
					_P += e[_i].p;
					_A += e[_i].a;
					_C += e[_i].c;
					_M += e[_i].m;
					_G += e[_i].g;
				}
			}
			if (_P <= P && _A <= A && _C <= C && _M <= M) {
				if (_G > f[o][_P][_A][_C][_M]) {
					f[o][_P][_A][_C][_M] = _G;
					g[o][_P][_A][_C][_M] = S;
				}
			}
		}
		for (int i = 0; i <= 36; ++i) {
			for (int j = 0; j <= 36; ++j) {
				for (int k = 0; k <= 36; ++k) {
					for (int l = 0; l <= 36; ++l) {
						if (i && f[o][i - 1][j][k][l] > f[o][i][j][k][l]) {
							f[o][i][j][k][l] = f[o][i - 1][j][k][l];
							g[o][i][j][k][l] = g[o][i - 1][j][k][l];
						}
						if (j && f[o][i][j - 1][k][l] > f[o][i][j][k][l]) {
							f[o][i][j][k][l] = f[o][i][j - 1][k][l];
							g[o][i][j][k][l] = g[o][i][j - 1][k][l];
						}
						if (k && f[o][i][j][k - 1][l] > f[o][i][j][k][l]) {
							f[o][i][j][k][l] = f[o][i][j][k - 1][l];
							g[o][i][j][k][l] = g[o][i][j][k - 1][l];
						}
						if (l && f[o][i][j][k][l - 1] > f[o][i][j][k][l]) {
							f[o][i][j][k][l] = f[o][i][j][k][l - 1];
							g[o][i][j][k][l] = g[o][i][j][k][l - 1];
						}
					}
				}
			}
		}
	}
	int res = 0;
	int S[2] = {0, 0};
	for (int i = 0; i <= 36; ++i) {
		for (int j = 0; j <= 36; ++j) {
			for (int k = 0; k <= 36; ++k) {
				for (int o = 0; o <= 36; ++o) {
					int _i = P - i, _j = A - j, _k = C - k, _o = M - o;
					if (_i >= 0 && _j >= 0 && _k >= 0 && _o >= 0 && f[0][i][j][k][o] + f[1][_i][_j][_k][_o] > res) {
						res = f[0][i][j][k][o] + f[1][_i][_j][_k][_o];
						S[0] = g[0][i][j][k][o];
						S[1] = g[1][_i][_j][_k][_o];
					}
				}
			}
		}
	}
	vector <int> res_vec;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 18; ++j) {
			if ((S[i] >> j) & 1) {
				res_vec.push_back(j + ran[i].fi - 1);
			}
		}
	}
	pt(SZ(res_vec));
	pt(res_vec);
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
