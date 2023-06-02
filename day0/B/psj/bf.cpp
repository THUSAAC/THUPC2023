#include<bits/stdc++.h>
using namespace std;

const int _ = 603; int P[_][_] , N , M , A[_];
bool operator <(vector < int > p, vector < int > q){
	sort(p.begin() , p.end()); sort(q.begin() , q.end());
	for(int i = 0 ; i < p.size() ; ++i)
		if(p[i] < q[i]) return 1;
		else if(p[i] > q[i]) return 0;
	return 0;
}

vector < int > ans;
void dfs(vector < int > pot, vector < int > ban){
	if(pot.size() == N - M){if(ans.empty() || pot < ans) ans = pot; return;}
	for(int i = 1 ; i <= M ; ++i)
		if(A[i] == pot.size())
			for(int j = 1 ; j <= N ; ++j){
				int x = P[i][j];
				if(find(pot.begin() , pot.end() , x) == pot.end() && find(ban.begin() , ban.end() , x) == ban.end()){
					ban.push_back(x); break;
				}
			}
	for(int x = 1 ; x <= N ; ++x)
		if(find(pot.begin() , pot.end() , x) == pot.end() && find(ban.begin() , ban.end() , x) == ban.end()){
			pot.push_back(x); dfs(pot , ban); pot.pop_back();
		}
}

int main(){
	cin >> N >> M; for(int i = 1 ; i <= M ; ++i) cin >> A[i];
	for(int i = 1 ; i <= M ; ++i) for(int j = 1 ; j <= N ; ++j) cin >> P[i][j];
	dfs({} , {}); for(auto t : ans) cout << t << ' ';
	//for(int i = 1 ; i <= N - M;  ++i) cout << i << ' ';
	return 0;
}