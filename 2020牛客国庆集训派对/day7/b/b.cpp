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
using pSI = pair <string, int>;
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
string s;

bool valid(string s) {
	if (SZ(s) < 2) return false;
	if (!isupper(s[0])) return false;
	for (int i = 1; i < SZ(s); ++i) {
		if (!islower(s[i]))
			return false;
	}
	return true;
}

int charType(char ch) {
	if (isalpha(ch)) return 1;
	return 0;
}

string work(string s) {
	string tmp = "";
	for (auto &ch : s) {
		if (isupper(ch)) tmp += ch;
	}
	if (SZ(tmp) < 2) return s;
	string res = tmp;
	tmp += " (";
	tmp += s;
	tmp += ")";
	return tmp;
}

void run() {
	vector <string> vec;
	string t = "";
	for (auto &ch : s) {
		if (t.empty()) t += ch;
		else {
			if (charType(ch) == charType(t.back())) t += ch;
			else {
				vec.push_back(t);
				t.clear();
				t += ch;
			}
		}
	}
	if (!t.empty()) vec.push_back(t);
	vector <pSI> _vec;
	for (int i = 0; i < SZ(vec); ++i) {
		string ss = vec[i];
		if (_vec.empty()) _vec.push_back(pSI(ss, valid(ss)));
		else {
			if (_vec.back().se == 1 && SZ(ss) == 1 && ss[0] == ' ' && i + 1 < SZ(vec) && valid(vec[i + 1])) {
				_vec.back().fi += ss;
				_vec.back().fi += vec[i + 1];
				i += 1;
			} else {
				_vec.push_back(pSI(ss, valid(ss)));
			}
		}
	}
	string res = "";
	for (auto &it : _vec) {
		if (it.se == 0) res += it.fi;
		else res += work(it.fi);
	}
	cout << res << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (getline(cin, s)) run();
//    for (int kase = 1; kase <= _T; ++kase) {
//        cout << "Case #" << kase << ": ";
//        run();
//    }
//	while (cin >> n) run();
//	run();
	return 0;
}
