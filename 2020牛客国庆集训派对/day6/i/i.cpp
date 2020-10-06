#include <iostream>
#include <vector>
#include <algorithm>

#define maxn 100005
using namespace std;

int w,h;
bool solve(int W,int H){
	return W<=w&&H<=h;
}

int main(){
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	scanf("%d%d",&w,&h);
	
	int flag=0;
	flag = flag|solve((a+b)*2,c+2*min(a,b));
	flag = flag|solve((a+c)*2,b+2*min(a,c));
	flag = flag|solve((b+c)*2,a+2*min(b,c));
	
	flag = flag|solve(3*b+a+c,c+a);
	flag = flag|solve(3*a+b+c,b+c);
	flag = flag|solve(3*c+a+b,a+b);
	
	flag = flag|solve(c+2*min(a,b),(a+b)*2);
	flag = flag|solve(b+2*min(a,c),(a+c)*2);
	flag = flag|solve(a+2*min(b,c),(b+c)*2);
	
	flag = flag|solve(c+a,3*b+a+c);
	flag = flag|solve(b+c,3*a+b+c);
	flag = flag|solve(a+b,3*c+a+b);
	
	if(flag)
		cout<<"Yes"<<endl;
	else
		cout<<"No"<<endl; 
} 