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
constexpr int N = 1e5 + 10; 
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
int n; 
ll has, f[N], g[N], a[N];

bool ok(ll x) {
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	ll use = 0;
	int r = 2;
	for (int i = 2; i < n; ++i) {
		use += r - i; 
		while (r < n && a[r + 1] < x - (r + 1 - i)) {
			use += x - (r + 1 - i) - a[r + 1];
			++r;
		}
		if (r == n && a[r] < x - (r - i)) f[i] = INFLL;
		else {
			f[i] = use;
		}
		use -= (x - 1) - a[i + 1];
	}
	int l = n - 1;
	use = 0;
	for (int i = n - 1; i > 1; --i) {
		use += i - l;
		while (l > 1 && a[l - 1] < x - (i - l + 1)) {
			use += x - (i - l + 1) - a[l - 1];
			--l;
		}
		if (l == 1 && a[l] < x - (i - l)) g[i] = INFLL;
		else g[i] = use;
		use -= (x - 1) - a[i - 1];
	}
//	if (x == 5) {
//		for (int i = 2; i < n; ++i)
//			dbg(i, f[i], g[i]);
//	}
	for (int i = 2; i < n; ++i) {
		if (x - a[i] + f[i] + g[i] <= has) return true;
	}
	return false;
}

void run() {
	rd(n, has);
	for (int i = 1; i <= n; ++i) rd(a[i]);
    ll l = *max_element(a + 1, a + 1 + n) + 1, r = 2e9, res = l - 1;
	while (r - l >= 0) {
		ll mid = (l + r) >> 1;
	//	dbg(mid);
		if (ok(mid)) {
			l = mid + 1;
			res = mid;
		} else {
			r = mid - 1;
		}
	}	
	pt(res);
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
