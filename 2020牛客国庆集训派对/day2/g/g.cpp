#include <iostream>

typedef long long ll;
using namespace std;

double solve(ll chicken,ll beef,ll lamb,ll nasi){
	double net_profit = 0;
	net_profit+=chicken*0.8;
	net_profit+=beef*1;
	net_profit+=lamb*1.2;
	net_profit+=nasi*0.8;
	
	double gross_profit = 0;
	gross_profit+=15.5*chicken;
	gross_profit+=32*beef;
	gross_profit+=40*lamb;
	gross_profit/=85;
	gross_profit+=0.2*nasi;
	
	return net_profit-gross_profit;
}

int main(){
	int n;
	int Case = 0;
	while(cin>>n){
		if(!n)break;
		ll chicken=0,beef=0,lamb=0,nasi=0;
		ll a,b,c,d;
		double result=0;
		while(n--){
			cin>>a>>b>>c>>d;
			chicken+=a;
			beef+=b;
			lamb+=c;
			nasi+=d;
			
			result+=solve(a,b,c,d);
		}
		printf("Case #%d: RM%.2lf\n",++Case,result);
	}
} 
