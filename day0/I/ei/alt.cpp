#include <algorithm>
#include <iostream>

using ull = unsigned long long;

int Mod;

int norm(int x) { return x >= Mod ? x - Mod : x; }
int reduce(int x) { return x < 0 ? x + Mod : x; }
int neg(int x) { return x ? Mod - x : 0; }
void add(int& x, int y) { if ((x += y - Mod) < 0) x += Mod; }
void sub(int& x, int y) { if ((x -= y) < 0) x += Mod; }
void fam(int& x, int y, int z) { x = (x + y * (ull)z) % Mod; }

const int _ = 2005;

int C[_][_], fac[_];
int f[_][_];
int pw1[_], pw2[_];

void pre(int n) {
	C[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = norm(C[i - 1][j - 1] + C[i - 1][j]);
	}
	fac[0] = 1; for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * (ull)i % Mod;
}

int main() {
	int n, m; std::cin >> n >> m >> Mod;
	
	pre(std::max(n, m));
	pw1[0] = 1; for (int i = 1; i <= n; ++i) pw1[i] = pw1[i - 1] * (ull)(n + m) % Mod;
	pw2[0] = 1; for (int i = 1; i <= m; ++i) pw2[i] = pw2[i - 1] * (ull)n % Mod;
	for (int i = 0; i <= n; ++i) pw1[i] = pw1[i] * (ull)C[n][i] % Mod;
	for (int i = 0; i <= m; ++i) pw2[i] = pw2[i] * (ull)C[m][i] % Mod * fac[m - i] % Mod;

	f[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= std::min(m, i); ++j) {
			if (j) f[i][j] = neg(f[i - 1][j - 1]);

			int val = (i - 1ULL) * (i - 2) % Mod;
			if (i >= 2) {
				            fam(f[i][j], val * 2, f[i - 2][j]);
				if (j >= 2) fam(f[i][j], val * 2, f[i - 2][j - 2]);
			}

			if (i >= 3) {
				if (j >= 1) fam(f[i][j], neg(val), f[i - 3][j - 1]);
				if (j >= 3) fam(f[i][j], val,      f[i - 3][j - 3]);
			}

			if (i >= 4) {
				val = (i - 1ULL) * (i - 2) % Mod * (i - 3) % Mod * (i - 4) % Mod;
				            fam(f[i][j], neg(val), f[i - 4][j]);
				if (j >= 2) fam(f[i][j], 2 * val,  f[i - 4][j - 2]);
				if (j >= 4) fam(f[i][j], neg(val), f[i - 4][j - 4]);
			}
		}
	}

	int ans = 0;
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= std::min(m, i); ++j)
			ans = (ans + pw1[n - i] * (ull)pw2[m - j] % Mod * f[i][j]) % Mod;
	std::cout << ans << '\n';

	return 0;
}
