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
priority_queue<pa,vector<pa>,greater<pa>> p; queue<int> rq; 
struct edge{int to,lt,v;}e[N*30]; int in[N*350],cnt;
void add(int x,int y,int v){e[++cnt].to=y; e[cnt].lt=in[x]; in[x]=cnt; e[cnt].v=v;}
int n,m,s,c[18],poi,dis[N*350],lg; //bool vis[N*200];
int node(int x,int y,int z){return ((z) * (lg+1) * n + (y) * n + (x));}
int getx(int id){return ((id) & (n - 1));}
int gety(int id){return (((id) >> lg) % (lg+1));}
int getz(int id){return (((id) >> lg) / (lg+1));}
void dfs(int x,int i,int j,int val)
{
	if(i==lg)	return;
	int y=node(x,i+1,j); if(dis[y]>val)	dis[y]=val,rq.push(y),dfs(x,i+1,j,val);
	y=node(x^(1<<i),i+1,j+1); if(dis[y]>val) dis[y]=val,rq.push(y),dfs(x^(1<<i),i+1,j+1,val);
}
void solve()
{
	memset(dis,48,sizeof(dis)); dis[s]=0; p.push(mp(0,s));
	while(!p.empty())
	{
		int x=p.top().se,v=p.top().fs; p.pop(); if(dis[x]!=v)	continue;
		int rx=getx(x),ri=gety(x),rj=getz(x);
		dfs(rx,ri,rj,dis[x]);
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
//	freopen("40.in","r",stdin);
//	freopen("40.ans","w",stdout);
	lg=read(),m=read(),s=read();
	n=1<<lg;
	for(int i=1;i<=lg;i++)	c[i]=read();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),v=read();
		add(x,y,v); add(y,x,v);
	}
	for(int i=0;i<n;i++)	for(int j=0;j<=lg;j++)
		add(node(i,lg,j),i,c[j]);
	solve(); //printf("%d ",all);
	for(int i=0;i<n;i++)	printf("%d ",dis[i]);
	puts("");
	return 0;
}
