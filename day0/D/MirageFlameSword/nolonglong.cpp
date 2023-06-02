#include <cstdio>
#include <cstring>
using namespace std;
int lbd[108], rbd[108];
char s[9];
int main(){
	int n, l, k, i, x, sum, pow10 = 1, base, si;
	scanf("%d", &n);
	scanf("%s", s);
	l = strlen(s) - 2;
	for (i = 1; i <= l; ++i) pow10 *= 10;
	base = pow10 * 10;
	if (s[0] == '1') {
		puts("1");
		return 0;
	}
	sscanf(s + 2, "%d", &x);
	lbd[1] = x * 10 - 5;
	rbd[1] = x * 10 + 5;
	for (i = 2; i <= n; ++i) {
		scanf("%s", s);
		if (s[0] == '1') {
			puts("1");
			return 0;
		}
		sscanf(s + 2, "%d", &x);
		lbd[i] = x * 10 - 5;
		rbd[i] = x * 10 + 5;
	}
	for (k = 2; k < pow10; ++k) {
		sum = 0;
		for (i = 1; i <= n; ++i) {
			si = (k * lbd[i] + base - 1) / base;
			if (si * base / k >= rbd[i]) break;
			sum += si;
		}
		if (i > n && sum == k) break;
	}
	printf("%d\n", k);
	return 0;
}