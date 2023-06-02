#include<bits/stdc++.h>
#include"testlib.h"
using namespace std;

const int TESTCASE = 16 , _ = 2e5 + 7;
vector < int > ch[_]; bool vis[_];
void dfs(int x){
	ensuref(!vis[x] , "Not a correct tree.");
	vis[x] = 1; for(auto t : ch[x]) dfs(t);
}

int main(){
	for(int i = 1 ; i <= TESTCASE ; ++i){
		freopen(("../data/" + to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		int T = inf.readInt(1 , 1e5); inf.readEoln();
		int sumN = 0;
		while(T--){
			int N = inf.readInt(2 , 1e5); sumN += N; inf.readEoln();
			for(int i = 1 ; i <= N ; ++i){
				inf.readInt(-1 , 1e9);
				if(i != N) inf.readSpace(); else inf.readEoln();
			}
			memset(vis , 0 , sizeof(bool) * (N + 3));
			for(int i = 1 ; i <= N ; ++i) ch[i].clear();
			for(int i = 1 ; i < N ; ++i){
				int u = inf.readInt(1 , N); inf.readSpace();
				int v = inf.readInt(1 , N); inf.readEoln();
				ch[u].push_back(v);
			}
			dfs(1);
			for(int i = 1 ; i <= N ; ++i)
				ensuref(vis[i] , "Not a correct tree.");
		}
		ensuref(sumN <= 2e5 , "sumN > 2e5");
		inf.readEof();
		cerr << i << endl;
	}
	return 0;
}