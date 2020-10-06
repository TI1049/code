#include <bits/stdc++.h>
using namespace std;
#define endl "\n" 
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
using db = long double;
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

void run() {
	rd(n);
	for (int i = 1; i <= n; ++i) {
		rd(a[i].fi, a[i].se);
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
