#include<bits/stdc++.h>
using namespace std;

int N, val[103]; string str[103];

int main(){
	ios::sync_with_stdio(0); cin >> N;
	for(int i = 1 ; i <= N ; ++i) cin >> str[i];
	int len = str[1].size() - 2;
	for(int i = 1 ; i <= N ; ++i){
		for(int j = 2 ; j < str[i].size(); ++j)
			val[i] = val[i] * 10 + str[i][j] - '0';
		if(str[i][0] == '1'){cout << 1 << endl; return 0;}
	}
	double lenv = pow(10 , -len);
	for(int i = 1 ; ; ++i){
		int sum = 0; bool flg = 1;
		for(int j = 1 ; j <= N ; ++j){
			int tarv = val[j] * lenv * i + 0.5;
			sum += tarv;
			flg &= int((double)tarv / i / lenv + 0.5) == val[j];
		}
		if(flg && sum == i){cout << i << endl; return 0;}
	}
	return 0;
}