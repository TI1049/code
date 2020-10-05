#include <bits/stdc++.h>
using namespace std;

int main() {
	set <int> se;
	se.insert(1);
	se.insert(2);
	se.insert(3);
	auto pos = se.begin();
   	auto pre = prev(pos);
	cout << *pre << endl;	
//	auto pos = se.lower_bound(3);
//	auto nx = next(pos);
//	if (nx == se.end()) cout << 1 << endl;
//	pos = se.begin();
//	auto pre = prev(pos);
//	cout << *pre << endl;
	
}
