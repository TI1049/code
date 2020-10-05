#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 10;
#define ALP 52
int n;
char s[N];
struct PAM{   
	struct node {
		int Next[ALP];
		int fail;
		ll num, len, sum;
		ll cnt;
		void init(int _len = 0) {
			memset(Next, 0, sizeof Next);
			fail = 0;
			num = cnt = sum = 0;
			len = _len;
		}
	}t[N];	
	int s[N];         
	int last;         
	int n;            
	int p;            
    int newnode(int len){ 
        t[p].init(len);
        return p++;
    }
    void init(){
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1; 		 
        t[0].fail = 1;
    }
    int get_fail(int x){ 
        while(s[n-t[x].len-1] != s[n]) x = t[x].fail;
        return x;
    }
    bool add(int c){
		bool F = 0;
		if (c >= 'a' && c <= 'z') c -= 'a';
		else c = 26 + c - 'A';
        s[++n] = c;
		int cur = get_fail(last);
		if(!t[cur].Next[c]){
            int now = newnode(t[cur].len + 2);
            t[now].fail = t[get_fail(t[cur].fail)].Next[c];
            t[cur].Next[c] = now;
            t[now].num = t[t[now].fail].num + 1;
            t[now].sum = t[t[now].fail].sum + t[now].len;
			F = 1;
		}
        last = t[cur].Next[c];
		++t[last].cnt;
		return F;
    }
    ll count(){
		ll res = 0;
		for (int i = p - 1;  i >= 0; --i) {
			t[t[i].fail].cnt += t[i].cnt;
		}
		for (int i = 2; i < p; ++i) res += t[i].cnt;
		return res;
    }
}pam;

int main() {
	scanf("%d%s", &n, s + 1);
	cout << (s + 1) << endl;
	pam.init();
	for (int i = 1; i <= n; ++i) pam.add(s[i]);
	cout << pam.p << endl;
	cout << pam.count() << endl;
	return 0;
}
