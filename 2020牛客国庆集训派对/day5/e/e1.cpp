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
pII a[N];

struct frac {
	ll x, y;
	void sim() {
		ll g = __gcd(x, y);
		x /= g;
		y /= g;
	}
	frac() {}
	frac(ll x, ll y) : x(x), y(y) { sim(); }
	bool operator < (const frac &other) const { return x * other.y < y * other.x; }
	bool operator <= (const frac &other) const { return x * other.y <= y * other.x; }
    frac operator + (const frac &u){
        ll p, q; 
        p = x * u.y + y * u.x;
        q = u.y * y;
        ll d = __gcd(p, q);
        p /= d; q /= d;
        return (frac){p, q};
    }
};

bool ok(frac x) {
	frac st = frac(0, 1);
	for (int i = 1; i <= n; ++i) {
		st = max(st, frac(a[i].fi, 1));
		frac ed = st + x;
		if (!(ed <= frac(a[i].se, 1))) return false;
		st = ed;
	}
	return true;
}

bool ok1(int x) {
	int st = 0;
	for (int i = 1; i <= n; ++i) {
		st = max(st, a[i].fi);
		int ed = st + x;
		if (ed > a[i].se) return false;
		st = ed;
	}
	return true;
}

int get() {
	int l = 0, r = 1000000, res = l;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (ok1(mid)) {
			res = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return res;
}

frac gao(vector <pII> vec) {
	frac res = frac(vec[0].se - vec[0].fi, 1);
	ll st = vec[0].fi;
	for (int i = 1; i < SZ(vec); ++i) {
		ll sum = vec[i].se - st;
		res = min(res, frac(sum, i + 1));
		ll x = vec[i].se;
		for (int j = 1, _i = i - j; _i >= 0 && j <= 60; ++j, --_i) {
			sum = x - vec[_i].fi;
			res = min(res, frac(sum, j + 1));
		}
		x = vec[i].fi;
		for (int j = 1, _i = i + j; _i < SZ(vec) && j <= 60; ++j, ++_i) {
			sum = vec[_i].se - x;
			res = min(res, frac(sum, j + 1));
		}
	}
	return res;
}

frac get2() {
	frac res = frac(a[1].se - a[1].fi, 1);
	vector <pII> vec;
	for (int i = 1; i <= n; ++i) {
		res = min(res, frac(a[i].se - a[i].fi, 1));
		if (vec.empty()) vec.push_back(a[i]);	
		else {
			if (a[i].fi >= vec.back().se) {
				res = min(res, gao(vec));
				vec.clear();
			}
			vec.push_back(a[i]);
		}
	}
	if (!vec.empty()) res = min(res, gao(vec));
	res.sim();
	return res;
}

void run() {
	rd(n);
	int Max = 0;
	for (int i = 1; i <= n; ++i) {
		rd(a[i].fi, a[i].se);
		chmax(Max, a[i].se - a[i].fi);
	}
	sort(a + 1, a + 1 + n, [&](pII a, pII b){
		if (a.fi == b.fi)
			return a.se < b.se;
		return a.fi < b.fi;
	});
	frac _res = get2();
	frac res = _res;
	if (!ok(_res)) {
		int base = get();
		frac l = frac(base, 1), r = _res, res = l;
		for (int i = 1; i <= 50; ++i) {
			frac mid = frac(l.x + r.x, l.y + r.y);
		//	frac _mid = mid + frac(base, 1);
			if (ok(mid)) {
				res = mid;
				l = mid;
			} else {
				r = mid;
			}
		}
	} 
	res.sim();
	cout << res.x << "/" << res.y << endl;
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
