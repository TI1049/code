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
constexpr int N = 4e3 + 10; 
constexpr int INF = 0x3f3f3f3f;
int n, lens, lent; 
char s[N], t[N];
int f_s[N][2], f_t[N][2], g[N][N];
int h_s[N][2], h_t[N][2];

void gao(char *s, int f[N][2]) {
	int pre[2] = {0, 0};
	int len = strlen(s + 1);
	f[0][0] = f[0][1] = 0;
	for (int i = 1; i <= len + 1; ++i) {
		f[i][0] = pre[0];
		f[i][1] = pre[1];
		if (i > len) break;
		pre[s[i] - '0'] = i;
	}
}

void gao1(char *s, int h[N][2]) {
	int len = strlen(s + 1);
	int nx[2] = {len + 1, len + 1};
	for (int i = len; i >= 0; --i) {
		h[i][0] = nx[0];
		h[i][1] = nx[1];
		if (i < 1) break;
		nx[s[i] - '0'] = i;
	}
}

void run() {
	cin >> (s + 1) >> (t + 1);
	lens = strlen(s + 1);
	lent = strlen(t + 1);
	gao(s, f_s); gao1(s, h_s);
	gao(t, f_t); gao1(t, h_t);
	memset(g, 0x3f, sizeof g);
	g[lens + 1][lent + 1] = 0;
//	for (int i = 0; i <= lens; ++i) g[i][lent + 1] = 0;
//	for (int i = 0; i <= lent; ++i) g[lens + 1][i] = 0;
	int tmp = -1;
	for (int i = lens; i >= 0; --i) {
		for (int j = lent; j >= 0; --j) if ((i == 0 && j == 0) || s[i] == t[j]) {
			for (int k = 0; k < 2; ++k) {
				int _i = h_s[i][k];
				int _j = h_t[j][k];
				if (i == 0 && j == 0) {
					if (g[_i][_j] + 1 < g[i][j]) {
						tmp = k;
					} else if (g[_i][_j] + 1 <= g[i][j]) {
						if (!k) tmp = 0;
					} 
				}
				chmin(g[i][j], g[_i][_j] + 1);
			}
		}
	}
	int num = g[0][0];
//	dbg(num);
//	return;
	string res = "";
//	res += tmp + '0';
	int i = 0, j = 0;
	while (num) {
		--num;
		for (int k = 0; k < 2; ++k) {
			int _i = h_s[i][k];
			int _j = h_t[j][k];
			dbg(num, _i, _j, g[_i][_j]);
			if (g[_i][_j] == num) {
				res += k + '0';
				i = _i;
				j = _j;
				break;
			}
		}
	}
	cout << res << endl;
//	pt(num);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	int _T = 1;
	while (_T--) run(); 
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
