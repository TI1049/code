#include <iostream>
#include <vector>

#define maxn 1005
using namespace std;

string s,t;
vector <string>v;

void solve(string a,string b){
	int flag=0;
	for(int i=0;i<a.size();i++){
		if(a[i]!=b[i]&&a[i]!='*'){
			flag=1;
			break;
		}
	}
	if(!flag)
		v.push_back(b);
}

int main(){
	cin>>s;
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>t;
		solve(s,t);
	}
	
	cout<<v.size()<<endl;
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<endl;
} 