#include<bits/stdc++.h>
using namespace std;

const int P = 1e9 + 7;
int T; long long N , M;

int solve(long long xorv , long long v){
	int ans = 0;
	for(int i = 0 ; i < v ; ++i)
		for(int j = 0 ; j + i < v ; ++j)
			if(xorv == (v ^ j ^ i)) ++ans;
	return ans;
}

int main(){
	for(cin >> T ; T ; --T){
		cin >> N >> M; long long xorv = 0;
		for(int i = 1 ; i <= N ; ++i) xorv ^= i;
		xorv ^= M; int ans = 0;
		for(int i = 1 ; i <= N ; ++i) ans = (ans + solve(xorv , i)) % P;
		cout << (ans + solve(xorv , M)) % P << '\n';
	}
	return 0;
}