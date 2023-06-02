#include<bits/stdc++.h>
using namespace std;

const int _ = 1e5 + 7; int N , A[_]; vector < int > nxt[_]; bool ans;
#define pii pair < int , int >
pii dfs(int x){
	vector < int > val; bool arb = 0;
	for(auto t : nxt[x]){pii ans = dfs(t); arb |= ans.second; val.push_back(ans.first);}
	sort(val.begin() , val.end());
	if(A[x] != -1 && val.size()){
		int L = val.back() + (val.size() >= 2 && val[val.size() - 2] == val.back()) , R = arb ? 1e9 + N : L;
		if(!(A[x] >= L && A[x] <= R)) ans = 0;
	}
	if(A[x] != -1) return pii(A[x] , 0);
	return pii(val.size() ? val.back() + (val.size() >= 2 && val[val.size() - 2] == val.back()) : 0 , val.empty() || arb);
}

int main(){
	ios::sync_with_stdio(0); int T;
	for(cin >> T ; T ; --T){
		cin >> N; for(int i = 1 ; i <= N ; ++i) nxt[i].clear();
		for(int i = 1 ; i <= N ; ++i) cin >> A[i];
		for(int i = 1 ; i < N ; ++i){int x , y; cin >> x >> y; nxt[x].push_back(y);}
		ans = 1; dfs(1); cout << (ans ? "Reasonable" : "Unreasonable") << endl;
	}
	return 0;
}