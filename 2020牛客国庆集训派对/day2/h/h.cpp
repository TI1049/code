#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int num[5][5];

bool jug(){
	
	int sum=0;
	int sum1=0;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			sum+=num[i][j];
			if(i==j) sum1+=num[i][j];
		}
	}
	
	if(sum1!=sum-sum1)
		return 1;
	
	for(int i=1;i<=4;i++){
		int total = 0;
		for(int j=1;j<=4;j++){
			if(i==j) continue;
			total+=num[i][j];
		}
		if(total!=num[i][i])return 1;
	}
	
	for(int j=1;j<=4;j++){
		int total = 0;
		for(int i=1;i<=4;i++){
			if(i==j) continue;
			total+=num[i][j];
		}
		if(total!=num[j][j])return 1;
	}
	
	return 0;
}

int main(){
	int n;
	cin>>n;
	for(int Case=1;Case<=n;Case++){
		memset(num,0,sizeof num);
		int flag=0;
		int a;
		vector <int>v1,v2;
		while(cin>>a){
			int t1=a/10;
			int t2=a%10;
			if(t1==0&&t2==0)break;
			num[t1][t2]++;
			v1.push_back(t1);
			v2.push_back(t2);
		}
		
		for(int i=0;i<v1.size();i++){
			if(i>=2&&v1[i]==v1[i-1]&&v1[i]==v1[i-2])
				flag=1;
		}
		
		for(int i=0;i<v2.size();i++){
			if(i>=2&&v2[i]==v2[i-1]&&v2[i]==v2[i-2])
				flag=1;
		}
		
		if(jug())
			flag = 1;
			
		if(flag)
			printf("Case #%d: Not Stroop\n",Case);
		else
			printf("Case #%d: Stroop\n",Case);
	}
}
