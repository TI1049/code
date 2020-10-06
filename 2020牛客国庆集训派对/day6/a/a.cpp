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
int n; 

ll ex_gcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll d = ex_gcd(b, a % b, x, y);
	ll temp = x;
	x = y;
	y = temp - a / b * y;
	return d;
}

bool liEu(ll a, ll b, ll c, ll &x, ll &y) {
	ll d = ex_gcd(a, b, x, y);
	if (c % d != 0) return 0;
	ll k = c / d;
	x *= k;
	y *= k;
	return 1;
}

void run() {
	rd(n);
	vector <int> fac;
	for (int i = 1; 1ll * i * i <= n; ++i) {
		if (n % i == 0) {
			if (i != 1 && i != n) fac.push_back(i);
			if (n / i != 1 && n / i != n) fac.push_back(n / i);
		}
	}
	sort(all(fac));
	fac.erase(unique(all(fac)), fac.end());
	int m = SZ(fac);
	for (int i = 0; i < m; ++i) {
		if ((n - 1) % (n / fac[i]) == 0) {
			cout << "YES\n";
			pt(1);
			pt((n - 1) / (n / fac[i]), fac[i]);
			return;
		}
		for (int j = i + 1; j < m; ++j) {
			ll a = n / fac[i];
			ll b = n / fac[j];
			ll c = n - 1;
			ll x, y;
			ll g = __gcd(a, b);
			ll t;
			if (liEu(a, b, c, x, y)) {
			//	if (x < 1) {
					t = b / g;
					x = (x % t + t) % t;
			//	}
			//	if (y < 1) {
					t = a / g;
					y = (y % t + t) % t;
			//	}
				cout << "YES\n";
				pt(2);
				pt(x, fac[i]);
				pt(y, fac[j]);
				return;
			}
		}
	}
	cout << "NO\n";
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
