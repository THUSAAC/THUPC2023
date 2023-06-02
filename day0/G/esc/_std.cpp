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
int a[444];
int op[444];
int last[222];
int f[404][404];
int s[404][404];
int rx[404][404];
int xcnt[404][404];
int g[404][404][404][2];
int lz[2][404][404][404];
const int inf=351493;
int F(int l,int r);
int G(int l,int r,int t,int to);
int F(int l,int r){
    if(l>r)return 0;
	if(s[l][r]!=-1)return f[l][r];
    if(op[r]>r)return 1+F(l,r-1);
    f[l][r]=inf;
	s[l][r]=0;
    int lxcnt=0;
    for(int i=l;i<=r;++i){
        if(op[i]<l){
            ++lxcnt;
        }
        if(i<op[i]&&op[i]<=r){
            if(lxcnt!=xcnt[l][r])continue;
            //TODO z on y
            //TODO no outer
            int left=F(l,i-1);
            int ycnt=0;//TODO
            int mid=1+ycnt+G(i+1,op[i],r+1,1);
            ycnt=0;//TODO
            int right=2+ycnt+F(op[i]+1,r);
            int tmp=dmax(left,mid);
            cmax(tmp,right);
            if(cmin(f[l][r],tmp)){
                s[l][r]=i;
            }
        }
        if(i>op[i]&&op[i]>=l){
            //TODO lx on top
            //TODO mid and right no y
            if(lxcnt!=xcnt[l][r])continue;
            //TODO no outer
            int left=xcnt[l][r]-lxcnt+G(l,op[i]-1,r+1,0);
            int ycnt=0;//TODO
            int mid=1+ycnt+F(op[i]+1,i-1);
            int right=2+ycnt+F(i+1,r);
            int tmp=dmax(left,mid);
            cmax(tmp,right);
            if(cmin(f[l][r],tmp)){
                s[l][r]=i;
            }
        }
    }
    int xp=l,xl=0;
    for(int i=l;i<=r;++i)
        if(op[i]<l){
            if(cmin(xp,op[i])){
                xl=i;
            }
        }
    if(xl==0)return f[l][r];
    int lxpmin=l,rxpmax=0;
    lxcnt=0;
    for(int i=l;i<xl;++i)
        if(op[i]<l){
            cmin(lxpmin,op[i]);
            ++lxcnt;
        }
    for(int i=xl+1;i<=r;++i)
        if(op[i]<l){
            cmax(rxpmax,op[i]);
        }
    if(lxpmin<rxpmax)return f[l][r];
    int left=1+lxcnt+G(l,xl-1,r+1,0);
    int ycnt=0;//TODO
    //TODO right no y
    int right=2+ycnt+F(xl+1,r);
    int tmp=dmax(left,right);
    if(cmin(f[l][r],tmp)){
        s[l][r]=0;
    }
    return f[l][r];
}
int G(int l,int r,int t,int to){ //to=0: near to self
    if(l>r)return 0;
    if(g[l][r][t][to]!=-1)return g[l][r][t][to];
	int mid=lz[to][t][r][l];
	if(mid>r)return F(l,r);
	if(rx[l][r]>mid)return inf;
    //TODO w on y
    int left=F(l,mid-1);
    int right=G(mid,r,t,to^1);
    int lycnt=0;//TODO
    return g[l][r][t][to]=dmax(left,lycnt+right);
}
int main()
{
    memset(s,-1,sizeof(f));
	memset(g,-1,sizeof(g));
	int m=io::F();
	for(int i=1;i<=m;++i){
		a[i]=io::F();
		if(last[a[i]])op[i]=last[a[i]];
		last[a[i]]=i;
	}
	for(int i=1;i<=m;++i){
		if(!op[i]){
			op[i]=last[a[i]];
		}
	}
    for(int l=1;l<=m;++l)
        for(int r=l;r<=m;++r){
            xcnt[l][r]=xcnt[l][r-1]+(op[r]<l);
            rx[l][r]=rx[l][r-1];
            if(op[r]<l){
                rx[l][r]=r;
            }
        }
	int ans=F(1,m);
    if(ans>=inf){
        puts("No solution.");
        return 0;
    }
    puts("Cleared.");
	printf("%d\n",ans);
    printf("%d\n",3*m/2);
    return 0;
}