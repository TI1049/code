#include <iostream>

#define maxn 1005
using namespace std;

int n,m;
int a[maxn],b[maxn];

int calc(int index,int t){
	t%=2*(b[index]-a[index]);
	
	if(t<=b[index]-a[index])
		return a[index]+t;
	else
		return 2*b[index]-a[index]-t;
}

void solve(int x,int y,int t){
	int cnt=0;
	for(int i=0;i<n;i++){
		int dis = calc(i,t);
//		cout<<dis<<endl;
		if(dis>=x&&dis<=y)
			cnt++;
	}
	printf("%d\n",cnt);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d%d",&a[i],&b[i]);
	}
	
	int x,y,t;
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&x,&y,&t);
		solve(x,y,t);
	}
} 