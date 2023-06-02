#include<bits/stdc++.h>
#include"testlib.h"
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
const int N=101;
int a[N][N],b[N][N],c[N][N];
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv); 
    int n = inf.readInt(); 
    assert(n == 100);
    int k = inf.readInt();
    assert(k>=0&&k<=n*n);
    //inf.readEoln();
    int curr = 0;
    rep(i,1,n){
    	rep(j,1,n)a[i][j]=inf.readInt(0,1);
    	//inf.readEoln();
	}
	int valid = ans.readInt();
	//ans.readEoln();
	int cvalid = ouf.readInt();
	//ouf.readEoln();
	if(valid!=cvalid)quitf(_wa,"Wrong Answer");
	if(valid == -1)quitf(_ok,"OK");
	else{
		rep(i,1,n){
    		rep(j,1,n)b[i][j]=ouf.readInt(0,1);
    		//ouf.readEoln();
		}
		rep(i,1,n)rep(j,1,n)curr+=b[i][j];
		if(curr!=k)quitf(_wa,"Wrong K");
		rep(k,1,n)rep(i,1,n)rep(j,1,n)c[i][j]^=(a[i][k]&b[k][j]);
		rep(i,1,n)rep(j,1,n)if(c[i][j]!=(a[i][j]&b[i][j]))quitf(_wa,"Invalid Matrix");
    	quitf(_ok, "OK");
	}
}
