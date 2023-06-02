#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define Fer(i,l,r) for(int i=l;i>=r;--i)
#if 1
#define pr(...) fprintf(stderr,__VA_ARGS__)
#else
#define pr(...) void(0)
#endif

typedef long long i64;
const int maxn=1e6,maxm=1e6,maxv=1e3,N=maxn+10,M=maxm+10;

int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}
int a[N];
int main(){
	int n=read(1,maxn);
	int m=read(1,maxm);
	Fe(i,1,n)a[i]=read(1,n);
	Fe(_,1,m){
		int x=read(1,n);
		int l=read(1,n),r=read(l,n);
		Fe(i,1,n)if(x>a[i])std::swap(x,a[i]);
		i64 s=0;
		Fe(i,l,r)s+=a[i];
		printf("%lld\n",s);
	}
	return 0;
}
