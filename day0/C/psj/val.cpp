#include<bits/stdc++.h>
#include"testlib.h"
using namespace std;

const int TESTCASE = 21;

int main(){
	for(int i = 1 ; i <= TESTCASE ; ++i){
		freopen(("../data/" + to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		int T = inf.readInt(1 , 10); inf.readEoln();
		while(T--){
			int l = inf.readInt(1 , 15); inf.readSpace();
			int n = inf.readInt(1 , 1 << l); inf.readEoln();
			for(int i = 1 ; i <= l ; ++i){
				inf.readInt(1 , 1e4);
				if(i != l) inf.readSpace(); else inf.readEoln();
			}
			set < string > strset;
			for(int i = 1 ; i <= n ; ++i){
				string str = inf.readToken(); inf.readEoln();
				for(auto t : str)
					ensuref(t == '0' || t == '1', "Not a binary string");
				ensuref(str.size() == l , "Length not l");
				ensuref(strset.count(str) == 0 , "Duplicate string");
				strset.insert(str);
			}
		}
		inf.readEof();
		cerr << i << endl;
	}
	return 0;
}