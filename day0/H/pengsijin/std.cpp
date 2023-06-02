#include<bits/stdc++.h>
using namespace std;

int main(){
	int N; cin >> N;
	for(int i = 0 ; i + 1 < N ; ++i,puts(""))
		for(int j = i + 1 ; j < N ; ++j)
			putchar('0' + __builtin_ctz(i ^ j));
	return 0;
}