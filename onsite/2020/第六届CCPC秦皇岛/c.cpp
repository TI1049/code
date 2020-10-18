#include <bits/stdc++.h>
using namespace std;
using db = long double;
#define dbg(x...) do { cout << #x << " -> "; err(x); } while (0)
void err() { cout << endl; }
template <class T, class... Ts> void err(const T& arg, const Ts&... args) {
	cout << arg << ' '; err(args...);
}

const db eps = 1e-6;
int sgn(db x) {
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
const int N = 1e5 + 10;
int w, h, n;

struct Point {
	db x, y;
	int vis, tp;
	Point(db x = 0, db y = 0, int vis = 1) : x(x), y(y), vis(vis) {}
	void scan() {
		scanf("%Lf%Lf", &x, &y);
	}
	Point operator - (const Point &b) const {
		return Point(x - b.x, y - b.y);
	}
	bool operator < (const Point &b) const {
		return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
	}
	db operator ^ (const Point &b) const {
		return x * b.y - y * b.x;
	}
	db dis(Point b) {
		return hypot(x - b.x, y - b.y);
	}
	db dis2(Point b) {
		return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
	}
}p;

struct Line {
	Point s, e;
	Line() {}
	Line(Point s, Point e) : s(s), e(e) {}
};

struct Polygon {
	vector <Point> p;
	Polygon() { p.clear(); }
	Polygon(int n) {
		p.clear();
		p.resize(n);
	}
	void add(Point x) {
		p.push_back(x);
	}
	int sze() { return p.size(); }
	Point& operator[](int x) {
		return p[(x + sze()) % sze()];
	}
	struct cmpNorm {
		Point p;
		cmpNorm(Point p) : p(p) {}
		bool operator () (Point a, Point b) {
			int d = sgn((a - p) ^ (b - p));
			if (d == 0) {
				return sgn(a.dis2(p) - b.dis2(p)) < 0;
			} else {
				return d > 0;
			}
		}
	};
	void norm() {
		Point mi = *p.begin();
		for (int i = 1; i < sze(); ++i) mi = min(mi, p[i]);
		sort(p.begin(), p.end(), cmpNorm(mi));
	}
	void norm(Point mi) {
		sort(p.begin(), p.end(), cmpNorm(mi));
	} 
//	int pointInConvex(Point q) {
//		int l = 1, r = sze() - 2;
//		while (r - l >= 0) {
//			int mid = (l + r) >> 1;
//			int a1 = sgn((p[mid] - p[0]))
//		} 
//	}
}po, _po;

db dis(Point a){
	return (p.x-a.x)*(p.x-a.x)+(p.y-a.y)*(p.y-a.y); 
}

Point getPoint(Point a){
	db dis_x = fabs(a.x-p.x);
	db dis_y = fabs(a.y-p.y);
//	cout<<dis_x<<' '<<dis_y<<endl;
	if(a.x==p.x&&a.y>p.y)
		return Point(p.x,h);
	else if(a.y==p.y&&a.x>p.x)
		return Point(w,p.y);
	else if(a.x==p.x&&a.y<p.y)
		return Point(p.x,0);
	else if(a.y==p.y&&a.x<p.x)
		return Point(0,p.y);
	else if(a.x>p.x&&a.y>p.y){
		Point new1_a;
		new1_a.x = w;
		new1_a.y = p.y+(w-p.x)*dis_y/dis_x;
		Point new2_a;
		new2_a.x = p.x+(h-p.y)*dis_x/dis_y;
		new2_a.y = h;
//		cout<<dis(new1_a)<<' '<<dis(new2_a)<<endl;
//		cout<<new1_a.x<<' '<<new1_a.y<<endl;
//		cout<<new2_a.x<<' '<<new2_a.y<<endl;
		if(sgn(dis(new1_a) - dis(new2_a)) <= 0)
			return new1_a;
		else
			return new2_a;
	}
	else if(a.x>p.x&&a.y<p.y){
		Point new1_a;
		new1_a.x = w;
		new1_a.y = p.y-(w-p.x)*dis_y/dis_x;
		Point new2_a;
		new2_a.x = p.x+p.y*dis_x/dis_y;
		new2_a.y = 0;
		if(sgn(dis(new1_a) - dis(new2_a)) <= 0)
			return new1_a;
		else
			return new2_a;
	}
	else if(a.x<p.x&&a.y>p.y){
		Point new1_a;
		new1_a.x = 0;
		new1_a.y = p.y+p.x*dis_y/dis_x;
		Point new2_a;
		new2_a.x = p.x-(h-p.y)*dis_x/dis_y;
		new2_a.y = h;
		if(sgn(dis(new1_a) - dis(new2_a)) <= 0)
			return new1_a;
		else
			return new2_a;
	}
	else if(a.x<p.x&&a.y<p.y){
		Point new1_a;
		new1_a.x = 0;
		new1_a.y = p.y-p.x*dis_y/dis_x;
		Point new2_a;
		new2_a.x = p.x-p.y*dis_x/dis_y;
		new2_a.y = 0;
		if(sgn(dis(new1_a) - dis(new2_a)) <= 0)
			return new1_a;
		else
			return new2_a;
	} 
	return Point(0, 0);
}

db calc(Point a, Point b) {
	if (sgn(a.x - b.x) == 0 || sgn(a.y - b.y) == 0) {
		return max(fabs(a.x - b.x), fabs(a.y - b.y));
	} else {
		assert(0);
	}
	return 0;
}

int main() {
	int _T; scanf("%d", &_T);
	for (int CAS = 1; CAS <= _T; ++CAS) {
		printf("Case #%d: ", CAS);
		scanf("%d%d", &w, &h);
		p.scan();
		scanf("%d", &n);
		po = Polygon(n);
		for (int i = 0; i < n; ++i) {
			po[i - 1].scan();
		}		
		po.norm(p);
		_po = Polygon(n + 4);
//		dbg(n);
		for (int i = 0; i < n; ++i) {
			_po[i] = getPoint(po[i]);
//			dbg(_po[i].x, _po[i].y);
			_po[i].vis = 1;
		}
		_po[n] = Point(0, 0, 0);
		_po[n + 1] = Point(w, 0, 0);
		_po[n + 2] = Point(w, h, 0);
		_po[n + 3] = Point(0, h, 0);
		for (int i = 0; i < n + 4; ++i) {
			if (sgn(_po[i].y) == 0) _po[i].tp = 1;
			else if (sgn(_po[i].x - w) == 0) _po[i].tp = 2;
			else if (sgn(_po[i].y - h) == 0) _po[i].tp = 3;
			else if (sgn(_po[i].x) == 0) _po[i].tp = 4;
		}
		sort(_po.p.begin(), _po.p.end(), [&](Point a, Point b) {
			if (a.tp != b.tp) return a.tp < b.tp;
			if (a.tp == 1) return sgn(a.x - b.x) <= 0;
			else if (a.tp == 2) return sgn(a.y - b.y) <= 0;
			else if (a.tp == 3) return sgn(a.x - b.x) >= 0;
			else if (a.tp == 4) return sgn(a.y - b.y) >= 0;
		});
//		for (int i = 1; i <= n + 4; ++i) {
//			dbg(i, _po[i].x, _po[i].y);
//		}
		db res = 0;
		for (int i = 1; i <= n + 100; ++i) {
			int _j = i - 1;
			for (int j = i - 1; ; --j) {
				if (_po[j].vis == 1) {
					_j = j;
					break;
				}
			}
			db now = 0;
			for (int j = i - 1; j >= _j; --j) {
				now += calc(_po[j], _po[j + 1]);
			}
			res = max(res, now);
		}
		printf("%.10Lf\n", res);
	}
	return 0;
}
