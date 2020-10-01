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
constexpr int N = 2e5 + 10; 
constexpr int INF = 0x3f3f3f3f;
int n, a[N]; 
pII r[N];

struct Cartesian_Tree {
	struct node {
		int id, val, fa;
		int son[2];
		node() {}
		node (int id, int val, int fa) : id(id), val(val), fa(fa) {
			son[0] = son[1] = 0;
		}
		bool operator < (const node &other) const {
			return val > other.val;
		}
	}t[N];
	int root;
	void init() {
		t[0] = node(0, INF, 0);
	}
	void build(int n, int *a) {
		for (int i = 1; i <= n; ++i) {
			t[i] = node(i, a[i], 0);
		}
		for (int i = 1; i <= n; ++i) {
			int k = i - 1;
			while (t[i] < t[k]) {
				k = t[k].fa;
			}
			t[i].son[0] = t[k].son[1];
			t[k].son[1] = i;
			t[i].fa = k;
			t[t[i].son[0]].fa = i;
		}
		root = t[0].son[1]; 
	}
	int dfs(int u) {
		if (!u) return 0;
		int lsze = dfs(t[u].son[0]);
		int rsze = dfs(t[u].son[1]);
		r[t[u].id] = pII(lsze, rsze);
		return lsze + rsze + 1;
	}
}CT;

struct SEG {
	int t[N << 2];
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = __gcd(t[id << 1], t[id << 1 | 1]);
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res = __gcd(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = __gcd(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg;

int gao(int l, int r, int _g) {
	if (l > r) return 0;
	int res = 0;
	while (l <= r) {
		_g = __gcd(_g, a[l]);
		int _l = l, _r = r, pos = _l;
		while (_r - _l >= 0) {
			int mid = (_l + _r) >> 1;
			if (seg.query(1, 1, n, l, mid) % _g == 0) {
				pos = mid;
				_l = mid + 1;
			} else {
				_r = mid - 1;
			}
		}
		chadd(res, 1ll * (pos - l + 1) * _g % mod);
		l = pos + 1;
	}
	return res;
}


int gao1(int l, int r, int _g) {
	if (l > r) return 0;
	int res = 0;
	while (l <= r) {
		_g = __gcd(_g, a[r]);
		int _l = l, _r = r, pos = _r;
		while (_r - _l >= 0) {
			int mid = (_l + _r) >> 1;
			if (seg.query(1, 1, n, mid, r) % _g == 0) {
				pos = mid;
				_r = mid - 1;
			} else {
				_l = mid + 1;
			}
		}
		chadd(res, 1ll * (r - pos + 1) * _g % mod);
		r = pos - 1;
	}
	return res;
}

void run() {
	rd(n);
	for (int i = 1; i <= n; ++i) rd(a[i]);
	CT.init();
	CT.build(n, a);
	CT.dfs(CT.root);
	seg.build(1, 1, n);
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		int now = 0;
		if (r[i].fi < r[i].se) {
			int _g = 0;
			for (int j = 0; j <= r[i].fi; ++j) {
				_g = __gcd(_g, a[i - j]);
				chadd(now, gao(i, i + r[i].se, _g));		
			}	
		} else {
			int _g = 0;
			for (int j = 0; j <= r[i].se; ++j) {
				_g = __gcd(_g, a[i + j]);
				chadd(now, gao1(i - r[i].fi, i, _g));
			}
		}
		chadd(res, 1ll * now * a[i] % mod);
//		dbg(i, i - r[i].fi, i + r[i].se, now);
	}
	pt(res);
}

int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr); cout.tie(nullptr);
//	cout << fixed << setprecision(20);
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
