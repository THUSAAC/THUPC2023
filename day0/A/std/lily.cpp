//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<cassert>
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
priority_queue<pa,vector<pa>,greater<pa>> p; queue<int> q,rq; 
struct edge{int to,lt,v;}e[N*60]; int in[N*200],cnt;
void add(int x,int y,int v){e[++cnt].to=y; e[cnt].lt=in[x]; in[x]=cnt; e[cnt].v=v;}
int f[N][18][18],n,m,s,c[18],poi,id[N*200],dis[N*200],lg,rid[200],rrd[200]; bool vis[N*200];
int all;
void solve()
{
	memset(dis,48,sizeof(dis)); dis[s]=0; p.push(mp(0,s));
	while(!p.empty())
	{
		int x=p.top().se; p.pop(); if(vis[x])	continue; vis[x]=1;
		if(x<n)	q.push(f[x][0][0]);
		else
		{
			//assert(x>=f[id[x]][0][0]);
			int rx=id[x],ni=x-f[rx][0][0],ri=rid[ni],rj=rrd[ni];
			if(ri+1<=lg)
			{
				int y=f[rx][ri+1][rj]; if(!y)	q.push(y);
				y=f[rx^(1<<ri)][ri+1][rj+1]; if(!y)	q.push(y);
			}
		}
		while(!q.empty())
		{
			int cx=q.front(); q.pop(); if(vis[cx])	continue;
			vis[cx]=1; dis[cx]=dis[x]; rq.push(cx);
			if(cx<n)	q.push(f[cx][0][0]);
			else
			{
				int rcx=id[cx],nci=cx-f[rcx][0][0],rci=rid[nci],rcj=rrd[nci];
				if(rci+1<=lg)
				{
					int y=f[rcx][rci+1][rcj]; if(!vis[y])	q.push(y);
					y=f[rcx^(1<<rci)][rci+1][rcj+1]; if(!vis[y])	q.push(y);
				}
			}
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
	freopen("34.in","r",stdin);
	freopen("out.txt","w",stdout);
	lg=read(),m=read(),s=read();
	n=1<<lg;
	for(int i=1;i<=lg;i++)	c[i]=read();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),v=read();
		add(x,y,v); add(y,x,v);
	}
	poi=n; int qwq=0;// printf("%d\n",lg);
	for(int j=0;j<=lg;j++)	for(int k=0;k<=j;k++)
		rid[qwq]=j,rrd[qwq]=k,qwq++;
	//printf("%d\n",qwq);
	for(int i=0;i<n;i++)	for(int j=0;j<=lg;j++)	for(int k=0;k<=j;k++)
		f[i][j][k]=++poi,id[poi]=i;
	for(int i=0;i<n;i++)	for(int j=0;j<=lg;j++)
		add(f[i][lg][j],i,c[j]);
	solve(); //printf("%d ",all);
	for(int i=0;i<n;i++)	printf("%d ",dis[i]);
	return 0;
}
