#include<bits/stdc++.h>
using namespace std;

const int P = 1e9 + 7; int T , dp[65][2][5]; long long N , M;
int upd(int x){return x + (x >> 31 & P);}
void inc(int &a , int b){a = upd(a + b - P);}

int solve(long long xorv , long long N){
	if(N <= 0) return 0;
	memset(dp , 0 , sizeof(dp)); dp[63][0][0] = 1;
	for(int i = 62 ; ~i ; --i)
		for(int j = 0 ; j < 2 ; ++j)
			for(int k = 0 ; k <= 4 ; ++k)
				if(dp[i + 1][j][k])
					for(int p = 0 ; p < 2 ; ++p)
						if(j || (N >> i & 1) >= p){
							int cur = k * 2 + p; bool nj = j | ((N >> i & 1) > p) , val = (xorv >> i & 1) ^ p;
							if(val){if(cur) inc(dp[i][nj][min(cur - 1 , 4)] , 2ll * dp[i + 1][j][k] % P);}
							else{
								inc(dp[i][nj][min(cur , 4)] , dp[i + 1][j][k]);
								if(cur >= 2) inc(dp[i][nj][min(cur - 2 , 4)] , dp[i + 1][j][k]);
							}
						}
	int sum = 0; for(int i = 0 ; i < 2 ; ++i) for(int j = 1 ; j <= 4 ; ++j) inc(sum , dp[0][i][j]);
	return sum;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	for(cin >> T ; T ; --T){
		cin >> N >> M; long long xorv = ((N + 1) >> 1 & 1) ^ (N & 1 ? 0 : N) ^ M;
		cout << (0ll + P + solve(xorv , N) + solve(xorv , M) - solve(xorv , M - 1)) % P << "\n";
	}
	return 0;
}
