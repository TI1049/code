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
using pCC = pair<char, char>;
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
constexpr int N = 1e6 + 10; 
int n; 
char s[N], t[N];
map <pCC, int> mp;

void run() {
	cin >> (s + 1) >> (t + 1);
	n = strlen(s + 1);
//	int cnt = 0;
//	for (auto &c1 : {'A', 'C', 'G', 'T'}) {
//		for (auto &c2 : {'A', 'C', 'G', 'T'}) {
//			if (c1 != c2) {
//				mp[pCC(c1, c2)] = ++cnt;
//			}
//		}
//	}
	for (int i = 1; i <= n; ++i) {
		char c1 = s[i];
		char c2 = t[i];
		if (c1 != c2) {
			++mp[pCC(c1, c2)];
		}
	}
	int res = 0;
	vector <char> vec({'A', 'C', 'G', 'T'});
	for (auto &c1 : vec) {
		for (auto &c2 : vec) {
			if (c1 != c2) {
				pCC t1 = pCC(c1, c2);
				pCC t2 = pCC(c2, c1);
				int Min = min(mp[t1], mp[t2]);
				res += Min;
				mp[t1] -= Min;
				mp[t2] -= Min;
			}
		}
	}
	do {
		char c1 = vec[0], c2 = vec[1], c3 = vec[2];
		pII t1 = pCC(c1, c2);
		pII t2 = pCC(c2, c3);
		pII t3 = pCC(c3, c1);
		int Min = min({mp[t1], mp[t2], mp[t3]});
		res += Min * 2;
		mp[t1] -= Min;
		mp[t2] -= Min;
		mp[t3] -= Min;
	} while (next_permutation(all(vec)));
	int sum = 0;
	for (auto &it : mp) sum += it.se;
	assert(sum % 4 == 0);
	res += sum / 4 * 3;
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
