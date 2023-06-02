#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

int N , M , P[303][603] , A[303]; bool vis[603];
int ansp[603] , outp[603];

int main(int argc, char **argv){
	registerTestlibCmd(argc, argv);
	N = inf.readInt(); M = inf.readInt();
	for(int i = 1 ; i <= M ; ++i) A[i] = inf.readInt();
	for(int i = 1 ; i <= M ; ++i)
		for(int j = 1 ; j <= N ; ++j) P[i][j] = inf.readInt();
	for(int i = 1 ; i <= N - M ; ++i){
		ansp[i] = ans.readInt(1 , N);
		outp[i] = ouf.readInt(1 , N);
	}

	int p = 1;
	for(int i = 1 ; i <= N - M ; ++i){
		ensuref(!vis[outp[i]] , "Method Invalid.");
		vis[outp[i]] = 1;
		if(A[p] == i){
			for(int x = 1 ; x <= N ; ++x)
				if(!vis[P[p][x]]){vis[P[p][x]] = 1; break;}
			++p;
		}
	}
	sort(ansp + 1 , ansp + N - M + 1);
	sort(outp + 1 , outp + N - M + 1);
	for(int i = 1 ; i <= N - M ; ++i)
		ensuref(ansp[i] == outp[i] , "Method not Optimal.");
	quitf(_ok, "Correct.");
	return 0;
}