#include<bits/stdc++.h>
#include"testlib.h"
using namespace std;

const int TESTCASE = 90;

int main(){
	for(int i = 1 ; i <= TESTCASE ; ++i){
		freopen(("../data/" + to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		int N = inf.readInt(3 , 600); inf.readSpace();
		int M = inf.readInt(1, (N - 1) / 2); inf.readEoln();
		int pre = 0;
		for(int i = 1 ; i <= M ; ++i){
			int T = inf.readInt(pre + 1 , N - M - 1);
			if(i != M) inf.readSpace(); else inf.readEoln();
		}
		for(int i = 1 ; i <= M ; ++i){
			static bool vis[603]; memset(vis, 0, sizeof(vis));
			for(int j = 1 ; j <= N ; ++j){
				int T = inf.readInt(1 , N);
				ensuref(!vis[T] , "permutation error.");
				vis[T] = 1;
				if(j != N) inf.readSpace(); else inf.readEoln();
			}
		}
		inf.readEof();
		cerr << i << endl;
	}
	return 0;
}