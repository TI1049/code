#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N=5e5+50, G=3, mod=998244353;
inline int add(int x,int y) {return (x+y>=mod) ? (x+y-mod) : (x+y);}
inline int dec(int x,int y) {return (x-y<0) ? (x-y+mod) : (x-y);}
inline int mul(int x,int y) {return (LL)x*y%mod;}
inline int power(int a,int b,int rs=1) {for(;b;b>>=1,a=mul(a,a)) if(b&1) rs=mul(rs,a); return rs;}
int n,k,g[N*8],f[N*8],tp[N*8],w[N*8],pos[N*8];
inline void init(int len) {	k=len<<1; for(int i=1;i<k;i++) pos[i]=(i&1) ? ((pos[i>>1]>>1)^(k>>1)) : (pos[i>>1]>>1);}
inline void dft(int *a) {
    for(int i=1;i<k;i++) if(pos[i]>i) swap(a[pos[i]],a[i]);
    for(int bl=1;bl<k;bl<<=1) {
        int tl=bl<<1, wn=power(G,(mod-1)/tl);
        w[0]=1; for(int i=1;i<bl;i++) w[i]=mul(w[i-1],wn);
        for(int bg=0;bg<k;bg+=tl)
            for(int j=0;j<bl;j++) {
                int &t1=a[bg+j], &t2=a[bg+j+bl], t=mul(t2,w[j]);
                t2=dec(t1,t); t1=add(t1,t);
            }
    }
}

inline void fuck(int *a,int *b,int len) {
    if(len==1) {b[0]=power(a[0],mod-2); return;}
    if(len!=1) fuck(a,b,len>>1);
    init(len);
    for(int i=0;i<len;i++) tp[i]=a[i];
    for(int i=len;i<k;i++) tp[i]=0;
    dft(b); dft(tp);
    for(int i=0;i<k;i++) b[i]=dec(mul(2,b[i]),mul(tp[i],mul(b[i],b[i])));
    reverse(b+1,b+k); dft(b);
    const int inv=power(k,mod-2);
    for(int i=0;i<len;i++) b[i]=mul(b[i],inv);
    for(int i=len;i<k;i++) b[i]=0;
}

//题目要求 n - 1 的划分数
int main() {
    cin>>n;n--;
    for(int k=1;(3*k*k-k)/2<=n;++k) {
        int v=(k&1) ? mod-1 : 1;
        g[(3*k*k-k)/2]+=v;
        g[(3*k*k+k)/2]+=v;
    } g[0]=1;
    for(k=1;k<=n;k<<=1);
   	fuck(g,f,k);
    cout<<f[n]<<endl;
}
