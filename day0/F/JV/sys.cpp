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
char command[100];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int _;cin>>_;
	if(_==1)rep(i,1,50){
		sprintf(command,"gen > %d.in",i);
		system(command);
		sprintf(command,"std < %d.in > %d.ans",i,i);
		system(command);
	}
	if(_==2){
		rep(i,1,50){
			sprintf(command,"spj %d.in %d.ans %d.ans",i,i,i);
			system(command);
		}
	}
	return 0;
}

