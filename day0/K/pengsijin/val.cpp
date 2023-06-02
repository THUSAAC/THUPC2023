#include<bits/stdc++.h>
#include"testlib.h"
using namespace std;

const int TESTCASE = 1;

int main(){
	for(int i = 1 ; i <= TESTCASE ; ++i){
		freopen(("../data/" + to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		int T = inf.readInt(5e4, 5e4); inf.readEoln();
		while(T--){
			inf.readLong(0 , (long long)1e18); inf.readSpace();
			inf.readLong(0 , (long long)1e18); inf.readEoln();
		}
		inf.readEof();
		cerr << i << endl;
	}
	return 0;
}