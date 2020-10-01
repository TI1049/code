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
using pDD = pair<db, db>;
using pDI = pair<db, int>;
using pLI = pair<ll, int>;
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
constexpr int N = 3e5 + 10; 
int n, r, a, b; 

const db eps = 1e-5;
const db PI = acos(-1.0L); 
int sgn(db x) { if (fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }
db sqr(db x) { return x * x; }
db fixOut(db x) { if (sgn(x) == 0) return 0; return x; }

struct Point {
	db x, y;
	Point(db x = 0, db y = 0) : x(x), y(y) {}
	void scan() { rd(x, y); }
	bool operator == (const Point &b) const { return sgn(x - b.x) == 0 && sgn(y - b.y) == 0; }
	bool operator < (const Point &b) const { return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x; }
	Point operator + (const Point &b) const { return Point(x + b.x, y + b.y); }
	Point operator - (const Point &b) const { return Point(x - b.x, y - b.y); }
	Point operator * (const db &b) const { return Point(x * b, y * b); }
	Point operator / (const db &b) const { return Point(x / b, y / b); }
	db operator ^ (const Point &b) const { return x * b.y - y * b.x; }
	db operator * (const Point &b) const { return x * b.x + y * b.y; }
	db len() { return hypot(x, y); }
	db len2() { return x * x + y * y; }
	db dis(Point b) { return hypot(x - b.x, y - b.y); }
	db dis2(Point b) { return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y); }
	Point trunc(db r) {
		db l = len();
		if (!sgn(l)) return *this;
		r /= l;
		return Point(x * r, y * r);
	}
};

struct Line {
	Point s, e;
	Line() {}
	Line(Point s, Point e) : s(s), e(e) {}
	bool operator == (const Line &b) const { return s == b.s && e == b.e; }
	void adjust() { if (e < s) swap(s, e); }
	db length() { return s.dis(e); }
	db getAngle() {
		db k = atan2(e.y - s.y, e.x - s.x);
		if (sgn(k) < 0) k += PI;
		if (sgn(k - PI) == 0) k -= PI;
		return k;
	}
	int relationPoint(Point p) {
		int c = sgn((p - s) ^ (e - s));
		if (c < 0) return 1;
		if (c > 0) return 2;	
		return 3;
	}
	bool pointOnSeg(Point p) { return sgn((p - s) ^ (e - s)) == 0 && sgn((p - s) * (p - e)) <= 0; }
	bool parallel(Line b) { return sgn((e - s) ^ (b.e - b.s)) == 0; }
	int segCrossSeg(Line b) {
		int d1 = sgn((e - s) ^ (b.s - s));
		int d2 = sgn((e - s) ^ (b.e - s));
		int d3 = sgn((b.e - b.s) ^ (s - b.s));
		int d4 = sgn((b.e - b.s) ^ (e - b.s));
		if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 2;
		return ((d1 == 0 && sgn((b.s - s) * (b.s - e)) <= 0) ||
				(d2 == 0 && sgn((b.e - s) * (b.e - e)) <= 0) ||
				(d3 == 0 && sgn((s - b.s) * (s - b.e)) <= 0) ||
				(d4 == 0 && sgn((e - b.s) * (e - b.e)) <= 0));
	}
	db disPointToLine(Point p) { return fabs((p - s) ^ (e - s)) / length(); } 
	db disPointToSeg(Point p) {
		if (sgn((p - s) * (e - s)) < 0 || sgn((p - e) * (s - e)) < 0)
			return min(p.dis(s), p.dis(e));
		return disPointToLine(p);
	}
	Point lineProg(Point p) { return s + (((e - s) * ((e - s) * (p - s))) / ((e - s).len2())); }
};

struct Circle {
	Point p; db r;
	Circle() {}
	Circle(Point p, db r) : p(p), r(r) {}
	Circle(db x, db y, db r) : p(Point(x, y)), r(r) {}
	bool operator == (const Circle &b) const { return (p == b.p) && sgn(r - b.r) == 0; }
	bool operator < (const Circle &b) const { return ((p < b.p) || ((p == b.p) && sgn(r - b.r) < 0)); }
	db area() { return PI * r * r; }
	db circumference() { return PI * r * 2; }
	Point getPoint(db rad) { return Point(p.x + cos(rad) * r, p.y + sin(rad) * r); }
	int relationPoint(Point b) {
		db dis = b.dis(p);
		if (sgn(dis - r) < 0) return 2;
		if (sgn(dis - r) == 0) return 1;
		return 0;
	}
	int relationSeg(Line b) {
		db dis = b.disPointToSeg(p);
		if (sgn(dis - r) < 0) return 2;
		if (sgn(dis - r) == 0) return 1;
		return 0;
	}
	int relationLine(Line b) {
		db dis = b.disPointToLine(p);
		if (sgn(dis - r) < 0) return 2;
		if (sgn(dis - r) == 0) return 1;
		return 0;
	}
	int pointCrossLine(Line b, Point &p1, Point &p2) {
		if (!(*this).relationLine(b)) return 0;
		Point a = b.lineProg(p);
		db d = b.disPointToLine(p);
		d = sqrt(r * r - d * d);
		if (sgn(d) == 0) {
			p1 = p2 = a;
			return 1;
		}
		p1 = a + (b.e - b.s).trunc(d);
		p2 = a - (b.e - b.s).trunc(d);
		return 2;
	}
};

void run() {
	rd(n, r, a, b);
	Line l = Line(Point(0, 0), Point(a, b));
	int f = 0;
	if (a == 0) f = 1, a = b;
	int L = 0, R = a;
	if (L > R) swap(L, R);
	vector <pLI> vec, _vec;
	for (int i = 1; i <= n; ++i) {
		Point p; p.scan();
		Point p1, p2;
		Circle c = Circle(p, r);
		int num = c.pointCrossLine(l, p1, p2);
		if (f) swap(p1.x, p1.y), swap(p2.x, p2.y);
		if (num) {
			db l = p1.x;
			db r = p2.x;
			if (sgn(l - r) > 0) swap(l, r);
		//	if (sgn(l - R) > 0) continue;
		//	if (sgn(L - r) > 0) continue;
		//	if (sgn(L - l) > 0) l = L;
		//	if (sgn(r - R) > 0) r = R;
			ll _l = ll(l * 1000000);
			ll _r = ll(r * 1000000);
			vec.push_back(pLI(_l, 1));
			vec.push_back(pLI(_r + 1, -1));
		}
	}
	sort(all(vec), [&](pLI a, pLI b) {
		return a.fi < b.fi;
	});
	for (auto &it : vec) {
		if (_vec.empty()) _vec.push_back(it);
		else {
			if (it.fi == _vec.back().fi) _vec.back().se += it.se;
			else {
				_vec.push_back(it);
			}
		} 
	}
	int res = 0, now = 0;
	for (auto &it : _vec) {
		now += it.se;
		chmax(res, now);
	}
	pt(res);
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
