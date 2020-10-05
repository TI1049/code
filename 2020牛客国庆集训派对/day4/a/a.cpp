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

vector <string> _get(string s) {
	vector <string> res;
	string t = "";
	for (auto &ch : s) {
		if (isdigit(ch)) t += ch;
		else {
			if (!t.empty()) res.push_back(t);
			t.clear();
			string _t = "";
			_t += ch;
			res.push_back(_t);
		}
	}
	if (!t.empty()) res.push_back(t);
//	for (auto &it : res) assert(SZ(it) > 0);
	return res;
}

int toInt(char ch) { return ch - '0'; }

char gao(string s, string t) {
	if (s == t) return '+';
	vector <string> _s(_get(s)), _t(_get(t));
//	pt(_s, _t);
//	return '+';
	for (int i = 0; i < min(SZ(_s), SZ(_t)); ++i) {
		string __s = _s[i];
		string __t = _t[i];
	//	dbg(__s, __t);
		int d_s = isdigit(__s[0]);
		int d_t = isdigit(__t[0]);
		if (d_s != d_t) {
			if (d_t) return '-';
			return '+';
		}
		if (__s != __t) {
			if (!d_s) {
				if (__s < __t) return '+';
				else return '-';
			} else {
				if (SZ(__s) != SZ(__t)) {
					if (SZ(__s) < SZ(__t)) return '+';
					else return '-';
				}	
				for (int j = 0; j < SZ(__s); ++j) {
					int n_s = toInt(__s[j]);
					int n_t = toInt(__t[j]);
					if (n_s != n_t) {
						if (n_s < n_t) return '+';
						else return '-';
					}
				}
			}
		}
	}
	if (SZ(s) > SZ(t)) return '-';
	else return '+';
}

void run() {
	rd(n);
	string s; rd(s);
	for (int i = 1; i <= n; ++i) {
		string t; rd(t);
//		cout << t << endl;
		pt(gao(s, t));
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
