#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define Rep(i, v) rep(i, 0, (int)v.size() - 1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr << #x << " = " << x
#define sp << " "
#define ln << endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline int inn() { int x;scanf("%d", &x);return x; }
const int N = 110;
typedef bitset<N> V;
int dp[N][N * N]; V cur[N][N * N];
struct LB {
	V v[N], p[N], r[N]; int k;
	inline int clear(int n) {
		rep (i, 1, n) v[i].reset(), p[i].reset(), r[i].reset();
		return k = 0;
	}
	inline int ins(V x, int n, int c) {
		V q; q.reset(); q[c] = 1;
		rep (i, 1, n) if (x[i]) {
			if (!v[i][i])
				return v[i] = x, p[i] = q, 0;
			x ^= v[i], q ^= p[i];
		}
		// col c is free
		return r[k++] = q, 0;
	}
	int vis[N];
	inline int _dp(int n, int c) {
		assert(k <= 20); V q;
		int all = (1 << k) - 1, *now = dp[c], *las = dp[c - 1];
		rep (i, 0, n * n) now[i] = las[i], cur[c][i] = cur[c - 1][i];
		memset(vis, 0, sizeof(int) * (n + 1));
		rep (s, 0, all) {
			q.reset();
			rep(i, 0, k - 1) if ((s >> i) & 1) q ^= r[i];
			int qc = q.count(); if (vis[qc]) continue; vis[qc] = 1;
			// debug(c)sp, debug(qc)ln;
			rep (i, qc, n * n) if (las[i - qc]) now[i] = 1, cur[c][i] = q;
		}
		return 0;
	}
}lb;
V a[N], A[N];
void bswap(V::reference a, V::reference b) {
	bool c = (bool)a; a = (bool)b; b = (bool)c;
}
inline int solve_col(int c, int n) {
	// \sum a[i][j] * b[j][c] = a[i][c] * b[i][c]
	// (a[i][i] ^ a[i][c]) * b[i][c] + \sum_{j!=i} a[i][j] * b[j][c] = 0
	rep (i, 1, n) A[i].reset();
	rep (i, 1, n) rep(j, 1, n) A[i][j] = a[i][j];
	rep (i, 1, n) A[i][i] = A[i][i] ^ A[i][c];
	rep (i, 1, n) rep(j, 1, i - 1) bswap(A[i][j], A[j][i]);
	// b[1][c] * A[1] + ... + b[n][c] * A[n] = 0
	lb.clear(n);
	rep (i, 1, n) lb.ins(A[i], n, i);
	lb._dp(n, c);
	return 0;
}
V ans[N];
inline int chk_ans(V *a, V *b, int n, int k) {
	rep (i, 1, n) rep(j, 1, n) {
		int res = 0;
		rep (t, 1, n) res ^= a[i][t] & b[t][j];
		assert(res == (a[i][j] & b[i][j]));
	}
	int cnt = 0;
	rep (i, 1, n) cnt += b[i].count();
	assert(cnt == k);
	return 0;
}
int main() {
	// freopen("data.in", "r", stdin);
	int n = inn(), k = inn();
	rep (i, 1, n) rep (j, 1, n) a[i][j] = inn();
	dp[0][0] = 1, cur[0][0].reset();
	rep (i, 1, n) solve_col(i, n);
	if (!dp[n][k]) return !printf("-1\n");
	for (int i = n, t = k; i >= 1; i--)
		ans[i] = cur[i][t], t -= ans[i].count();
	rep (i, 1, n) rep (j, 1, i - 1) bswap(ans[i][j], ans[j][i]);
	// chk_ans(a, ans, n, k);
	printf("1\n");
	rep (i, 1, n) rep (j, 1, n) printf("%d%c", (int)ans[i][j], " \n"[j == n]);
	return 0;
}
