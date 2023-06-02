#include<bits/stdc++.h>
#include"testlib.h"
using namespace std;

const int TESTCASE = 17;

int main(){
	for(int i = 1 ; i <= TESTCASE ; ++i){
		freopen(("../data/" + to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		int N; N = inf.readInt(1 , 100); inf.readEoln();
		static string str[103];
		for(int i = 1 ; i <= N ; ++i){
			str[i] = inf.readToken(); inf.readEoln();
			ensuref(str[i].size() == str[1].size() , "Length not consistent");
			ensuref(str[i].size() <= 8, "Length > 6");
			ensuref(str[i][1] == '.', "Not a correct decimal");
		}
		for(int i = 1 ; i <= N ; ++i) str[i].erase(str[i].begin() + 1);
		int sum = 0; for(int i = 1 ; i <= N ; ++i) sum += atoi(str[i].c_str());
		ensuref(sum == (int)pow(10 , str[i].size() - 1), "Sum not equal to 1");
		inf.readEof();
		cerr << i << endl;
	}
	return 0;
}