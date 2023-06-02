#include<bits/stdc++.h>
#include <chrono>
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


unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 rnd(seed);
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n=100;int k=rnd()%(n*n)+1;
	printf("%d %d\n",n,k);
	rep(i,1,n){
		rep(j,1,n)printf("%d%c",rand()%2," \n"[j==n]);
	}
	return 0;
}

