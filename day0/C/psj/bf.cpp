#include<bits/stdc++.h>
using namespace std;

const int _ = 1 << 15 | 1 , P = 998244353; int T , L , N , prob[16] , val[_]; bool vis[_];
int poww(long long a , int b){int tms = 1; while(b){if(b & 1) tms = tms * a % P; a = a * a % P; b >>= 1;} return tms;}

int prb[1 << 15 | 1];
bool check(int mask , int id){
	int cnt = 0; for(int i = 0 ; i < 1 << L && cnt < 2 ; ++i) cnt += ((i ^ id) & mask) == 0 && vis[i];
	assert(cnt); return cnt == 1;
}

void work(int pos){
	memset(prb , 0 , sizeof(prb)); prb[0] = 1; int ans = 0;
	for(int i = 0 ; i < 1 << L ; ++i){
		if(check(i , pos)) continue;
		int cycle_prob = 1;
		for(int j = 0 ; j < L ; ++j) if(!(i >> j & 1)) cycle_prob = 1ll * cycle_prob * (1 - prob[j] + P) % P;
		int step = poww(P + 1 - cycle_prob , P - 2); ans = (ans + 1ll * prb[i] * step) % P;
		for(int p = 0 ; p < 1 << L ; ++p)
			if((i & p) == i && i != p){
				int probvalue = step;
				for(int j = 0 ; j < L ; ++j)
					if(!(i >> j & 1)) probvalue = 1ll * probvalue * (p >> j & 1 ? prob[j] : 1 - prob[j] + P) % P;
				prb[p] = (prb[p] + 1ll * prb[i] * probvalue) % P;
			}
	}
	cout << ans << "\n";
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	for(cin >> T ; T ; --T){
		cin >> L >> N; memset(vis , 0 , sizeof(vis));
		for(int j = 0 ; j < L ; ++j){cin >> prob[j]; prob[j] = 1ll * prob[j] * poww(10000 , P - 2) % P;}  reverse(prob, prob + L);
		for(int j = 1 ; j <= N ; ++j){string s; cin >> s; int tms = 0; for(auto t : s){tms = tms << 1 | (t - '0');} val[j] = tms; vis[tms] = 1;}
		for(int j = 1 ; j <= N ; ++j) work(val[j]);
	}
	return 0;
}