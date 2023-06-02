#include<bits/stdc++.h>
using namespace std;

const int MAXN=660;
int n,m;
int a[MAXN];
int p[MAXN];
int cnt[MAXN];

int main(){
	for(int T=1;T<=90;T++){
		string infile = std::to_string(T)+".in";
	    freopen(infile.c_str(),"r",stdin);
		scanf("%d%d",&n,&m);
		assert(n>=1&&n<=600);
		assert(m>=1&&m<=600);
		for(int i=1;i<=m;i++){
			scanf("%d",&a[i]);
			assert(a[i]>a[i-1]&&a[i]<n-m);
		}
		for(int i=1;i<=m;i++){
			memset(cnt,0,sizeof(cnt));
			for(int j=1;j<=n;j++){
				scanf("%d",&p[i]);
				assert(p[i]>=1&&p[i]<=n);
				cnt[p[i]]++;
			}
			for(int i=1;i<=n;i++)assert(cnt[i]==1);
		}
		char c;scanf("%c",&c);assert(c=='\n');
		assert(scanf("%c",&c)==EOF);
		cout<<T<<" OK\n";
	}
}
