//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<ctime>
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
	freopen("seed.txt","r",stdin);
	srand(time(0)); int qaq=read()+rand();
	fclose(stdin);
	freopen("seed.txt","w",stdout);
	printf("%d\n",qaq);
	fclose(stdout);
	freopen("in.txt","w",stdout);
	int n=1<<(rand()%10),m=rand()%2000+1,s=rand()%n;
	printf("%d %d %d\n",n,m,s); 
	for(int i=1;i<=20;i++)	printf("%d ",(rand()<<8)^rand()); printf("\n");
	for(int i=1;i<=m;i++)
	{
		int x=rand()%n,y=rand()%n,v=rand();
		printf("%d %d %d\n",x,y,v);
	}
	fclose(stdout);
	return 0;
}

