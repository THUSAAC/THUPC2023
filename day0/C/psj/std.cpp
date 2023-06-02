#include<bits/stdc++.h>
using namespace std;

const int pw315 = 14348907 , _ = pw315 + 2 , P = 998244353;
void inc(int &a , int b){a = (a + b >= P ? a + b - P : a + b);}
int poww(long long a , int b){int tms = 1; while(b){if(b & 1) tms = tms * a % P; a = a * a % P; b >>= 1;} return tms;}

int pw3[16] , lowest2[_] , reveal[_];
void initialization(){
	pw3[0] = 1; for(int i = 1 ; i <= 15 ; ++i) pw3[i] = pw3[i - 1] * 3;
	for(int i = 0 ; i < pw315 ; ++i){
		lowest2[i] = -1; for(int j = 0 , t = i ; j < 15 ; ++j , t /= 3) if(t % 3 == 2){lowest2[i] = j; break;}
		if(lowest2[i] != -1) reveal[i] = reveal[i - pw3[lowest2[i]]] | 1 << lowest2[i];
	}
}

int T , L , N , prob[15];

int val[1 << 15 | 1] , dp[1 << 15 | 1][16] , sumval;
void getdp(){
	for(int j = 0 ; j < L ; ++j){cin >> prob[j]; prob[j] = 1ll * prob[j] * poww(10000 , P - 2) % P;} 
	reverse(prob, prob + L);
	memset(dp , 0 , sizeof(dp)); memset(val , 0 , sizeof(val)); val[0] = 1; sumval = 0;
	for(int i = 0 ; i < 1 << L ; ++i){
		auto trans = [&](){
			for(int j = 0 ; j < L ; ++j)
				if(!(i >> j & 1)){
					dp[i | (1 << j)][j + 1] = (dp[i | (1 << j)][j + 1] + 1ll * dp[i][j] * prob[j]) % P;
					dp[i][j + 1] = (dp[i][j + 1] + 1ll * dp[i][j] * (P + 1 - prob[j])) % P;
				}else inc(dp[i][j + 1] , dp[i][j]);
		};
		trans(); val[i] += dp[i][L]; int cycle_prob = 1;
		for(int j = 0 ; j < L ; ++j) if(!(i >> j & 1)) cycle_prob = 1ll * cycle_prob * (1 - prob[j] + P) % P;
		int step = poww(P + 1 - cycle_prob , P - 2);
		memset(dp[i] , 0 , sizeof(dp[i])); dp[i][0] = 1ll * val[i] * step % P; trans();
		val[i] = 1ll * val[i] * step % P; inc(sumval , val[i]);
	}
}

int belong[_] , ans[1 << 15 | 1] , COUNT;
void getbelong(){
	memset(belong , 0 , sizeof(belong)); memset(ans , 0 , sizeof(ans));
	for(int j = 1 ; j <= N ; ++j){string s; cin >> s; int tms = 0; for(auto t : s){tms = tms * 3 + (t - '0');} belong[tms] = j;}
	for(int i = 0 ; i < pw3[L] ; ++i){
		if(lowest2[i] != -1){
			int p = belong[i - pw3[lowest2[i]]] , q = belong[i - 2 * pw3[lowest2[i]]];
			if(p == -1 || q == -1 || (p != 0 && q != 0)) belong[i] = -1;
			else belong[i] = p + q;
		}
		if(belong[i] > 0){inc(ans[belong[i]] , val[reveal[i] ^ ((1 << L) - 1)]); ++COUNT;}
	}
}

int main(){
	clock_t start = clock();
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); initialization();
	for(cin >> T ; T ; --T){
		cin >> L >> N; getdp(); getbelong(); for(int j = 1 ; j <= N ; ++j) cout << (sumval - ans[j] + P) % P << "\n";
		cerr << COUNT << endl; COUNT = 0;
	}
	clock_t end = clock();
	cerr << (end - start) * 1.0 / CLOCKS_PER_SEC << endl;
	return 0;
}