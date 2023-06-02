//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#define ll long long
#define inf 20021225
#define N 100010
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
int f[520][520],dis[520][520],c[21];
int main()
{
//	freopen("in.txt","r",stdin);
	int lg=read(),n=1<<lg,m=read(),s=read();
	memset(f,48,sizeof(f));
	for(int i=1;i<=lg;i++)	c[i]=read();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),v=read();
		f[x][y]=f[y][x]=min(f[x][y],v);
	}
	for(int x=0;x<n;x++)	for(int y=0;y<n;y++)
		f[x][y]=f[y][x]=min(f[x][y],c[__builtin_popcount(x^y)]);
	for(int k=0;k<n;k++)	for(int i=0;i<n;i++)	for(int j=0;j<n;j++)
		f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	for(int i=0;i<n;i++)	printf("%d ",f[s][i]);
	return 0;
}

