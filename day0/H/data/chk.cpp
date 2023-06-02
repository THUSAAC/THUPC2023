#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

int N;
struct matrix{
	bitset < 1003 > val[1003];
	friend matrix operator *(matrix p , matrix q){
		//q is in transpose form
		matrix R;
		for(int i = 0 ; i < N ; ++i)
			for(int j = 0 ; j < N ; ++j)
				R.val[i][j] = (p.val[i] & q.val[j]).any();
		return R;
	}
};

int main(int argc, char** argv){
	registerTestlibCmd(argc, argv);
	N = inf.readInt(2 , 1000);
	matrix M[10];
	for(int i = 0 ; i + 1 < N ; ++i){
		string s = ouf.readToken();
		if(i == 0 && s == "-1")
			quitf(_wa , "There is an answer, but you do not provide one.");
		if(s.size() != N - 1 - i) quitf(_wa , "Output format error.");
		for(int j = 0 ; j < s.size() ; ++j){
			ensuref(isdigit(s[j]) , "Output format error.");
			M[s[j] - '0'].val[i].set(i + j + 1);
			M[s[j] - '0'].val[i + j + 1].set(i);
		}
	}
	for(int j = 0 ; j < 10 ; ++j){
		matrix now = M[j] , pw2 = now * now , pw3 = now * pw2;
		for(int k = 0 ; k < N ; ++k)
			ensuref(!pw3.val[k][k] , "There is a 3-cycle with the same color.");
		for(int k = 0 ; k < N ; ++k)
			ensuref((pw3.val[k] & pw2.val[k]).none() , "There is a 5-cycle with the same color.");
	}
	quitf(_ok , "Accepted.");
	return 0;
}