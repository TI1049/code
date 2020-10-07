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
int n, q, a[N], k[N];
char op[N][5];

struct SEG {
	struct node {
		ll base, sum, lazy;
		node() { base = sum = 0; }
		node(ll base, ll sum) : base(base), sum(sum) {}
		void up(ll x) {
			sum += base * x;
			lazy += x;
		}
		node operator + (const node &other) const {
			node res = node();
			res.base = base + other.base;
			res.sum = sum + other.sum;
			return res;
		}
	}t[N << 2];
	void down(int id) {
		ll &lazy = t[id].lazy;
		if (lazy) {
			t[id << 1].up(lazy);
			t[id << 1 | 1].up(lazy);
			lazy = 0;
		}
	}
	void build(int id, int l, int r) {
		if (l == r) {
			t[id] = node();
			t[id].base = a[l] - a[l - 1];
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	void update(int id, int l, int r, int ql, int qr, ll v) {
		if (ql > qr) return;
		if (l >= ql && r <= qr) {
			t[id].up(v);
			return;
		}
		down(id);
		int mid = (l + r) >> 1;
		if (ql <= mid) update(id << 1, l, mid, ql, qr, v);
		if (qr > mid) update(id << 1 | 1, mid + 1, r, ql, qr, v);
		t[id] = t[id << 1] + t[id << 1 | 1];
	}
	ll query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (l >= ql && r <= qr) return t[id].sum;
		int mid = (l + r) >> 1;
		down(id);
		ll res = 0;
		if (ql <= mid) res += query(id << 1, l, mid, ql, qr);
		if (qr > mid) res += query(id << 1 | 1, mid + 1, r, ql, qr);
		return res;
	}
}seg;

void run() {
	rd(n, q);
	a[0] = 0;
	int tot = 0; int has = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> op[i];
		rd(a[i], k[i]);
		if (op[i][0] == '-') tot += k[i];
		else has += k[i];
	}
	seg.build(1, 1, n);
	for (int i = 1; i <= n; ++i) {
		int f = 1;
		if (op[i][0] == '+') f = -1;
		seg.update(1, 1, n, i + 1, n, k[i] * f);
	}
	for (int i = 1, x; i <= q; ++i) {
		rd(x);
		if (has + x < tot) {
			cout << "INFINITY\n";
			continue;
		}
		seg.update(1, 1, n, 1, n, -x);
		int l = 1, r = n, pos = n + 1;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (seg.query(1, 1, n, mid, mid) > 0) {
				pos = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		pt(seg.query(1, 1, n, pos, n));
		seg.update(1, 1, n, 1, n, x);
	}
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
