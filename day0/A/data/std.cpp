//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<cassert>
#include<iostream>
#include<ctime>
#define ll long long
#define inf 20021225
#define N 150010
#define pa pair<int,int>
#define mp make_pair
#define fs first
#define se second
using namespace std;
int read()
{
    int s=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')    f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9')    s=s*10+ch-'0',ch=getchar();
    return s*f;
}
priority_queue<pa,vector<pa>,greater<pa>> p; queue<int> rq; 
struct edge{int to,lt,v;}e[N*30]; int in[N*200],cnt;
void add(int x,int y,int v){e[++cnt].to=y; e[cnt].lt=in[x]; in[x]=cnt; e[cnt].v=v;}
int f[18][18][N],n,m,s,c[18],poi,dis[N*200],lg,rid[200],rrd[200],id[18][18]; //bool vis[N*200];
void dfs(int x,int i,int j,int val)
{
	if(i==lg)	return;
	int y=f[i+1][j][x]; if(dis[y]>val)	dis[y]=val,rq.push(y),dfs(x,i+1,j,val);
	y=f[i+1][j+1][x^(1<<i)]; if(dis[y]>val) dis[y]=val,rq.push(y),dfs(x^(1<<i),i+1,j+1,val);
}
void solve()
{
	memset(dis,48,sizeof(dis)); dis[s]=0; p.push(mp(0,s));
	while(!p.empty())
	{
		int x=p.top().se,v=p.top().fs; p.pop(); if(dis[x]!=v)	continue;
		if(x<n)	dfs(x,0,0,dis[x]);
		else
		{
			int rx=x&(n-1),ni=x>>lg,ri=rid[ni],rj=rrd[ni];
			dfs(rx,ri,rj,dis[x]);
		}
		rq.push(x);
		while(!rq.empty())
		{
			x=rq.front(); rq.pop();
			for(int i=in[x];i;i=e[i].lt)
			{
				int y=e[i].to;
				if(dis[y]>dis[x]+e[i].v)
				{
					dis[y]=dis[x]+e[i].v,p.push(mp(dis[y],y));
				}
			}
		}
	}
}
int main()
{
	//freopen("35.in","r",stdin);
	//freopen("35.out","w",stdout);
	lg=read(),m=read(),s=read();
	n=1<<lg;
	for(int i=1;i<=lg;i++)	c[i]=read();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),v=read();
		add(x,y,v); add(y,x,v);
	}
	poi=n; int qwq=0;// printf("%d\n",lg);
	for(int i=0;i<n;i++)	f[0][0][i]=i;
	for(int j=1;j<=lg;j++)	for(int k=0;k<=j;k++)
		++qwq,rid[qwq]=j,rrd[qwq]=k,id[j][k]=qwq;
	//printf("%d\n",qwq);
	for(int i=0;i<n;i++)	for(int j=1;j<=lg;j++)	for(int k=0;k<=j;k++)
		f[j][k][i]=id[j][k]*n+i;
	for(int i=0;i<n;i++)	for(int j=0;j<=lg;j++)
		add(f[lg][j][i],i,c[j]);
	solve(); //printf("%d ",all);
	for(int i=0;i<n;i++)	printf("%d ",dis[i]);
	puts("");
	cerr<<clock()<<endl;
	return 0;
}
