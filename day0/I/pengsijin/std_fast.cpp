#include<bits/stdc++.h>
using namespace std;

const int _ = 2003; int f[_][_] , g[_][_][2][2] , h[_][_][2] , l[_][_][2][2][2][2] , n , m , P;
void add(int &x , int y){x = x + y >= P ? x + y - P : x + y;}

int main(){
	cin >> n >> m >> P; f[0][0] = 1;
	for(int i = 0 ; i <= n ; ++i)
		for(int j = 0 ; j <= m ; ++j){
			if(i) f[i][j] = (1ll * (n + m - i - j) * g[i - 1][j][0][0] + 1ll * (n - i) * g[i - 1][j][1][0] + h[i - 1][j][0]) % P;
			else if(j) f[i][j] = 1ll * n * f[i][j - 1] % P;
			for(int p = 0 ; p < 2 ; ++p)
				for(int q = 0 ; q < 2 ; ++q)
					g[i][j][p][q] = (
						(p == q ? f[i][j] : 0) + 
						(i ? 1ll * i * g[i - 1][j][p][0] : 0) +
						(j && !q ? 1ll * j * g[i][j - 1][p][1] : 0)
					) % P;
			for(int p = 0 ; p < 2 ; ++p)
				for(int q = 0 ; q < 2 ; ++q)
					for(int r = 0 ; r < 2 ; ++r)
						for(int s = 0 ; s < 2 ; ++s){
							l[i][j][p][q][r][s] = (
								((!p || !q) && (!r || !s) ? f[i][j] : 0) +
								(i ? 1ll * i * l[i - 1][j][!p][q][r][0] : 0) +
								(!s && j ? 1ll * j * l[i][j - 1][p][!q][r][1] : 0)
							)% P;
						}
			for(int p = 0 ; p < 2 ; ++p)
				h[i][j][p] = (
					l[i][j][!p][p][p][p] + 
					(i ? 1ll * i * h[i - 1][j][0] : 0) +
					(!p && j ? 1ll * j * h[i][j - 1][1] : 0)
				) % P;
		}
	cout << f[n][m] << endl;
	return 0;
}