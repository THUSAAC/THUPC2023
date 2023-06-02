#include<bits/stdc++.h>
using namespace std;

const int MAXN=2010;
int n,m,p; 
long long f0[MAXN][MAXN][2][2];
long long f1[MAXN][MAXN][2];
long long f2[MAXN][MAXN][2][2][2][2];
long long f3[MAXN][MAXN];
inline int add(int x,int y){return (x+y>=p)?x+y-p:x+y;}

int main(){
	scanf("%d%d%d",&n,&m,&p);
	f3[0][0]=1;
	for(long long i=0;i<=n;i++){
		for(long long j=0;j<=m;j++){
			for(long long lk=0;lk<=1;lk++)for(long long nw=0;nw<=1;nw++)
				if(!(nw==1&&lk==1))f3[i][j]+=f0[i][j][lk][nw];
			for(long long nw=0;nw<=1;nw++)f2[i][j][nw][nw][nw==0][nw==1]=add(f2[i][j][nw][nw][nw==0][nw==1],f1[i][j][nw]);
			for(long long lk=0;lk<=1;lk++)for(long long nw=0;nw<=1;nw++)for(long long w=0;w<=1;w++)for(long long b=0;b<=1;b++)
				if(!(nw==1&&lk==1))if(!(w==1&&b==1))f3[i][j]+=f2[i][j][lk][nw][w][b];
			f3[i][j]%=p;
			for(long long lk=0;lk<=1;lk++){
				f0[i+1][j][lk][0]=(f0[i+1][j][lk][0]+f0[i][j][lk][0]*(n-i)+f0[i][j][lk][1]*(n-i))%p;
				f0[i][j+1][lk][1]=(f0[i+1][j][lk][1]+f0[i][j][lk][0]*(m-j))%p;
			}
			f1[i+1][j][0]=(f1[i+1][j][0]+f1[i][j][0]*(n-i)+f1[i][j][1]*(n-i))%p;
			f1[i][j+1][1]=(f1[i+1][j][1]+f1[i][j][0]*(m-j))%p;
			for(long long lk=0;lk<=1;lk++){
				for(long long w=0;w<=1;w++){
					for(long long b=0;b<=1;b++){
						f2[i+1][j][lk][0][w^1][b]=(f2[i+1][j][lk][0][w^1][b]+f2[i][j][lk][0][w][b]*(n-i)+f2[i][j][lk][1][w][b]*(n-i))%p;
						f2[i][j+1][lk][1][w][b^1]=(f2[i][j+1][lk][1][w][b^1]+f2[i][j][lk][0][w][b]*(m-j))%p;
					}
				}
			}
			
			if(j!=m){
				f0[i][j+1][0][1]=(f0[i][j+1][0][1]+f3[i][j]*i)%p;
				f0[i][j+1][1][1]=(f0[i][j+1][1][1]+f3[i][j]*j)%p;
				f1[i][j+1][1]=(f1[i][j+1][1]+f3[i][j])%p; 
			}else{
				f0[i+1][j][0][0]=(f0[i+1][j][0][0]+f3[i][j]*i)%p;
				f0[i+1][j][1][0]=(f0[i+1][j][1][0]+f3[i][j]*j)%p;
				f1[i+1][j][0]=(f1[i+1][j][0]+f3[i][j])%p; 
			}
		}
	}
	printf("%d\n",f3[n][m]);
}
