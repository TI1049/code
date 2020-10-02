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
constexpr int N = 5e2 + 10; 
constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
int n, m;
ll D[N][N], R[N][N], G[N], g[N][N], f[N][N], h[N][N];

void run() {
	rd(n, m);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			rd(g[i][j]);
		}
		for (int j = 1; j <= m; ++j) {
			rd(R[i][j]);
		}
		for (int j = 1; j <= m; ++j) {
			rd(D[i][j]);
		}
	}
	rd(*G);
	for (int i = 1; i <= *G; ++i) rd(G[i]);
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
		}
	}
//	reverse(G + 1, G + 1 + *G);
	memset(h, 0x3f, sizeof h);
	memset(h[0], 0, sizeof h[0]);
	memset(f, 0x3f, sizeof f);
	memset(f[0], 0, sizeof f[0]);
	for (int i = 0; i < *G; ++i) {
		int x = G[i + 1];
		for (int j = 1; j <= n; ++j) if (f[i][j] < INF) {
			for (int k = 1; k <= n; ++k) {
				if (R[k][x] != -1) {
					if (!i) {
						f[1][k] = R[k][x];
						continue;
					}
					chmin(f[i + 1][k], f[i][j] + R[k][x] + g[j][k]);
				}
			}
		}
	}
	reverse(G + 1, G + 1 + *G);
	for (int i = 0; i < *G; ++i) {
		int x = G[i + 1];
		for (int j = 1; j <= n; ++j) if (h[i][j] < INF) {
			for (int k = 1; k <= n; ++k) {
				if (D[k][x] != -1) {
					if (!i) {
						h[1][k] = D[k][x];
						continue;
					}
					chmin(h[i + 1][k], h[i][j] + D[k][x] + g[j][k]);
				}
			}
		}
	}
	ll res = INF;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			chmin(res, f[*G][i] + h[*G][j]);
		   //	+ g[i][j]);
		}
	}
	pt(res);
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
