#include<bits/stdc++.h>
using namespace std;

#define int long long
mt19937_64 rnd(time(0) ^ getpid());
int gen(int l , int r){return l + (int)(rnd() % (r - l + 1));}

signed main(){
	int T = 5e4; cout << T << endl;
	for(int i = 0 ; i <= 5 ; ++i)
		for(int j = 0 ; j <= 5 ; ++j, --T)
			cout << i << ' ' << j << endl;
	cout << "0 2000000013\n3 2000000013\n"; T -= 2;
	while(T--){
		int LIMN_GEN = gen(1 , 100);
		int LIMN = LIMN_GEN <= 2 ? 100 : (LIMN_GEN <= 4 ? 1e4 : (LIMN_GEN <= 8 ? 1e9 : 1e18)) , N = gen(0 , LIMN);
		int LIMM_GEN = gen(1 , 100);
		int LIMM = LIMM_GEN <= 2 ? 100 : (LIMM_GEN <= 4 ? 1e4 : (LIMM_GEN <= 8 ? 1e9 : 1e18)) , M = gen(0 , LIMM);
		int TYPE_GEN = gen(1 , 100);
		if(TYPE_GEN <= 2) cout << N << ' ' << (((N + 1) >> 1 & 1) ^ (N & 1 ? 0 : N)) << endl;
		else cout << N << ' ' << M << endl;
	}
	return 0;
}