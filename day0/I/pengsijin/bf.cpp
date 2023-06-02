#include<bits/stdc++.h>
using namespace std;

int P , n , m , edge[12] , ans;

void dfs(int x){
	if(x == n + m + 1){
		for(int i = 1 ; i <= n + m ; ++i){
			int cur = i , stp = 0 , cnt[2] = {};
			do{++cnt[cur <= n]; cur = edge[cur];}while(++stp <= n + m && cur != i);
			if(cur == i && cnt[1] * cnt[0] % 2 == 1) return;
		}
		++ans; return;
	}
	for(int i = 1 ; i <= (x <= n ? n + m : n) ; ++i){edge[x] = i; dfs(x + 1);}
}

int main(){cin >> n >> m >> P; dfs(1); cout << ans % P << endl; return 0;}