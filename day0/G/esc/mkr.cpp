#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io
{
	int F()
	{
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G()
	{
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
std::mt19937_64 gen(std::random_device{}());
int R(int l, int r){
    return std::uniform_int_distribution<>(l,r)(gen);
}
int p[1111];
int main()
{
    int n=1500;
    printf("%d\n",n);
    int k=n/2;
    for(int i=1;i<=k;++i)p[i]=i;
    for(int i=1;i<=k;++i){
        std::swap(p[i],p[R(1,i)]);
    }
    printf("%d ",p[1]);
    for(int i=2;i<=n/2;++i){
       printf("%d %d%c",p[i],p[i]," \n"[i==n/2+1]);
    }
    printf("%d\n",p[1]);
    // for(int i=1;i<=n/2;++i){
    //     printf("%d ",p[i]);
    // }
    // for(int i=1;i<=n/2;++i){
    //     printf("%d%c",p[i]," \n"[i==k]);
    // }
    // printf("1 ");
    // for(int i=2;i<=n/2;++i){
    //     printf("%d ",i);
    // }
    // printf("1 ");
    // for(int i=n/2;i>=2;--i){
    //     printf("%d ",i);
    // }
    // printf("%d ",p[749]);
    // for(int i=1;i<=n/4;++i){
    //     printf("%d ",p[i]);
    // }
    // printf("%d ",p[749]);
    // for(int i=n/4,q=n/4+1;i;--i,++q){
    //     printf("%d %d %d ",p[q],p[i],p[q]);
    // }
    // puts("");
    // for(int i=1;i<=k;++i){
    //     printf("%d ",p[i]);
    // }
    // for(int l=1,r=k;l<=r;++l,--r){
    //     printf("%d %d ",p[l],p[r]);
    // }
    // puts("");
    return 0;
}