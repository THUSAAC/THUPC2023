#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
const int p=998244353;
typedef long long ll;
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second

void add(int &x,int y){x=(x+y>=p)?(x+y-p):x+y;}
int qpow(int x,int y){int ret=1;while(y){if(y&1)ret=1ll*ret*x%p;x=1ll*x*x%p;y>>=1;}return ret;}

mt19937_64 rnd(time(0));
int n,k,a[101][101],b[101][101],c[101][101];
bool valid;
bitset<101>x[101];
int f[101][101],dp[101][10005],fr[101][10005];bitset<101>w[101][101];
void find(){
	memset(f,0,sizeof(f));
	rep(i,1,n){
		int u=0;vector<int>free;free.clear();
		rep(i,1,n)x[i].reset();
		rep(j,1,n)rep(k,1,n)x[j][k]=a[j][k];
		rep(j,1,n)x[j][j]=x[j][j]^a[j][i];
		rep(j,1,n){
			bool flg=0;
			rep(k,u+1,n)if(x[k][j]){
				swap(x[k],x[u+1]);flg=1;
				rep(l,u+2,n)if(x[l][j])x[l]^=x[u+1];
				u++;
				break;
			}
			if(!flg)free.pb(j);
		}
		int m=free.size();
		assert(m+u==n);
		//if(m>1)printf("Free variables:%d\n",m);
		rep(j,0,(1<<m)-1){
			bitset<101>y;
			rep(k,0,m-1)y[free[k]]=(j>>k)&1;
			for(int k=u;k;k--){
				int l=x[k]._Find_first();
				rep(ll,l+1,n)if(x[k][ll])y[l]=y[l]^y[ll];
			}
			//printf("Y:");rep(i,1,n)printf("%d",(int)y[i]);puts("");
			int l=y.count();
			//printf("count:%d ",l);
			f[i][l]=1;w[i][l]=y;
		}
	}
}
void merge(){
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	rep(i,0,n-1)rep(j,0,n*i)if(dp[i][j])rep(k,0,n)if(f[i+1][k]){
		dp[i+1][j+k]=1;fr[i+1][j+k]=k;
	}
	//rep(i,1,n*n)printf("%d",dp[n][i]);puts("");
	//rep(i,0,n*n)assert(dp[n][i]|(!dp[n][i+1]));
	if(!dp[n][k])printf("-1\n"),valid=0;
	else{
		printf("1\n");
		valid=1;
		int kk=k;
		for(int i=n;i;i--){
			int l=fr[i][kk];
			assert(w[i][l].count()==l);
			rep(j,1,n)b[j][i]=w[i][l][j];
			rep(k,1,n){
				int mm=0;
				rep(l,1,n)mm^=a[k][l]&b[l][i];
				assert(mm==(a[k][i]&b[k][i]));
			}
			kk-=l;
		}
	}
}
void solve(){
	find();
	merge();
}
void check(){
	if(!valid)return;
	rep(i,1,n)rep(j,1,n)if(b[i][j]!=0&&b[i][j]!=1){
		printf("Invalid b[%d][%d].\n",i,j);
		exit(0);
	}
	int cnt=0;
	rep(i,1,n)rep(j,1,n)cnt+=b[i][j];
	if(cnt!=k){
		printf("Invalid number of ones.\n");
		exit(0);
	}
	memset(c,0,sizeof(c));
	rep(k,1,n)rep(i,1,n)rep(j,1,n)c[i][j]^=a[i][k]&b[k][j];
	rep(i,1,n)rep(j,1,n)if(c[i][j]!=(a[i][j]&b[i][j])){
		printf("Error at %d %d.\n",i,j);
		//exit(0);
	}
}
void onetest(){
	cin>>n>>k;
	rep(i,1,n)rep(j,1,n)cin>>a[i][j];
	solve();
	check();
	if(valid)rep(i,1,n){
		rep(j,1,n)printf("%d ",b[i][j]);puts("");
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	onetest();return 0;
	int _;cin>>_;while(_--){
		n=100;k=rnd()%(n*n)+1;
		rep(i,1,n)rep(j,1,n)a[i][j]=rand()%2;
		rep(i,1,n){
			//rep(j,1,n)printf("%d ",a[i][j]);
			//printf("\n");
		}
		solve();
		//printf("Solved.\n");
		check();
		rep(i,1,n){
			//rep(j,1,n)printf("%d ",b[i][j]);
			//printf("\n");
		}
	}
	return 0;
}

