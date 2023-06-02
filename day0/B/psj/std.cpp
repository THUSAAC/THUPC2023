#include<bits/stdc++.h>
using namespace std;

const int _ = 603; int S[_][_] , N , M , A[_] , ans[_]; bool vis[_];

bool check(){
	static bool tmp[_]; memcpy(tmp , vis , sizeof(tmp));
	static int mn[_]; memset(mn , 0x3f , sizeof(mn));
	for(int i = 1 ; i <= M ; ++i)
		for(int j = 1 ; j <= N ; ++j){
			int t = S[i][j];
			if(tmp[t]){mn[t] = min(mn[t] , A[i]);}
			else{tmp[t] = 1; break;}
		}
	vector < int > pot; for(int i = 1 ; i <= N ; ++i) if(vis[i]) pot.push_back(i);
	sort(pot.begin() , pot.end() , [&](int p , int q){return mn[p] < mn[q];});
	for(int i = 0 ; i < pot.size() ; ++i) ans[i + 1] = pot[i];
	for(int i = 1 ; i <= pot.size() ; ++i) if(mn[ans[i]] < i) return 0;
	return 1;
}

int main(){
	cin >> N >> M;
	for(int i = 1 ; i <= M ; ++i) cin >> A[i];
	for(int i = 1 ; i <= M ; ++i) for(int j = 1 ; j <= N ; ++j) cin >> S[i][j];
	for(int i = 1 ; i <= N ; ++i){vis[i] = 1; if(!check()) vis[i] = 0;}
	assert(check()); for(int i = 1 ; i <= N - M ; ++i) cout << ans[i] << " \n"[i == N - M];
	return 0;
}