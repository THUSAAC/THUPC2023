#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io
{
	int F()
	{
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G()
	{
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
const int maxm=2008;
int ori[maxm];
int a[maxm];
int op[maxm];
int last[maxm];
bool f[maxm][maxm][2];
int s[maxm][maxm][2];
int ly[maxm][maxm];
const int inf=351493;
int to[maxm];
int rr[maxm];
int xl[maxm];
#define BOTH 0
int formid, visit;
void dfs(int l,int r,int t,int offset){
	if(l>r)return;
	if(ly[l][r]<=r){
		to[a[ly[l][r]]]=t^offset;
		dfs(l,ly[l][r]-1,t^1,offset);
		dfs(ly[l][r]+1,r,1,offset^t^1);
	}
	else{
		if(s[l][r][t]<0){
			dfs(l,-s[l][r][t]-1,0,offset);
			dfs(-s[l][r][t]+1,r,BOTH,offset);
		}
		else{
			if(s[l][r][t]<op[s[l][r][t]]){
				to[a[s[l][r][t]]]=offset;
				dfs(l,s[l][r][t]-1,1,offset);
				dfs(s[l][r][t]+1,op[s[l][r][t]]-1,1,offset^1);
				dfs(op[s[l][r][t]]+1,r,BOTH,offset);
			}
			else{
				to[a[s[l][r][t]]]=offset^1;
				dfs(l,op[s[l][r][t]]-1,0,offset);
				dfs(op[s[l][r][t]]+1,s[l][r][t]-1,1,offset);
				dfs(s[l][r][t]+1,r,BOTH,offset^1);
			}
		}
	}
}
void init(int L,int R){
	for(int i=L;i<=R;++i){
		last[a[i]]=0;
		op[i]=0;
	}
	for(int i=L;i<=R;++i){
		if(last[a[i]])op[i]=last[a[i]];
		last[a[i]]=i;
	}
	for(int i=L;i<=R;++i){
		if(!op[i]){
			op[i]=last[a[i]];
		}
	}
	for(int r=R;r>=L;--r){
		ly[r+1][r]=R+1;
		for(int l=r;l>=L;--l){
			ly[l][r]=ly[l+1][r];
			if(op[l]>r){
				ly[l][r]=l;
			}
		}
	}
}
int min[maxm];
void insert(int p,int v){
	for(int i=p;i;i-=i&-i){
		cmin(min[i],v);
	}
}
int query(int p,int rb){
	int ret=inf;
	for(int i=p;i<=rb;i+=i&-i){
		cmin(ret,min[i]);
	}
	return ret;
}
long long h[maxm],hs[maxm];
std::map<long long,int> hmap;
void dp(int L,int R){
	for(int l=R;l>=L;--l){
		int rx=0;
		xl[l-1]=l;
		for(int r=l;r<=R;++r){
			xl[r]=xl[r-1];
			if(op[r]<l){
				cmin(xl[r],op[r]);
			}
		}
		memset(min,63,sizeof(int)*(R-L+5));
		for(int r=R;r>=l;--r){
			rr[r]=query(xl[r]-L+1,l-L+1);
			if(op[r]<l){
				insert(op[r]-L+1,r);
			}
		}
		
		for(int r=l;r<=R;++r){
			if(op[r]<l){
				rx=r;
			}
			if(ly[l][r]>r){
				f[l][r][0]=1;
				int rmax=l;
				for(int k=l;k<=r;++k){
					//++formid;
					if(op[k]>rmax){
						//++visit;
						if(rx<k){
							bool tmp=f[l][k-1][1]|f[k+1][op[k]-1][1]|f[op[k]+1][r][BOTH];
							f[l][r][0]&=tmp;
							if(tmp==0){
								s[l][r][0]=k;
								goto skip;
							}
						}
						if((xl[k]==l||r<rr[k])&&rx<op[k]){
							bool tmp=f[l][r][0]&=f[l][k-1][0]|f[k+1][op[k]-1][1]|f[op[k]+1][r][BOTH];
							f[l][r][0]&=tmp;
							if(tmp==0){
								s[l][r][0]=op[k];
								goto skip;
							}
						}
						rmax=op[k];
					}
				}
				if(xl[r]!=l){
					int xlp=op[xl[r]];
					if(xl[xlp-1]==l||r<rr[xlp-1]){
						bool tmp=f[l][xlp-1][0]|f[xlp+1][r][BOTH];
						f[l][r][0]&=tmp;
						if(tmp==0){
							s[l][r][0]=-xlp;
							goto skip;
						}
					}
				}
				skip:;
				f[l][r][1]=f[l][r][0];
				s[l][r][1]=s[l][r][0];
			}
			else{
				f[l][r][0]=f[l][r][1]=1;
				int ly=::ly[l][r];
				if(rx<ly){
					f[l][r][0]=f[l][ly-1][1]|f[ly+1][r][1];
				}
				if(xl[ly]==l||r<rr[ly]){
					f[l][r][1]=f[l][ly-1][0]|f[ly+1][r][1];
				}
			}
		}
	}
	if(f[L][R][BOTH]){
		//fprintf(stderr,"formid=%d visit=%d\n",formid,visit);
		puts("No solution.");
		exit(0);
	}
	dfs(L,R,BOTH,0);
}
int main()
{
	int m=io::F();
	for(int i=1;i<=m;++i){
		ori[i]=io::F();
	}
	for(int i=1;i<=m/2;++i){
		h[i]=(long long)rand()<<31|rand();
	}
	hmap[0]=0;
	int pa=0;
	for(int i=1;i<=m;++i){
		a[++pa]=ori[i];
		hs[pa]=hs[pa-1]^h[ori[i]];
		if(hmap.count(hs[pa])&&hmap[hs[pa]]<pa){
			int l=hmap[hs[pa]]+1;
			init(l,pa);
			dp(l,pa);
			pa=l-1;
		}
	}
	//fprintf(stderr,"formid=%d visit=%d\n",formid,visit);
	puts("Cleared.");
	printf("%d\n",m*3/2);
	std::vector<int> v[2],vis(m/2+1);
	for(int i=1;i<=m;++i){
		putchar('1'+(to[ori[i]]^vis[ori[i]]));
		v[to[ori[i]]^vis[ori[i]]].push_back(ori[i]);
		while(v[0].size()&&v[1].size()&&v[0].back()==v[1].back()){
			putchar('0');
			v[0].pop_back();
			v[1].pop_back();
		}
		vis[ori[i]]=1;
	}
	puts("");
	assert(v[0].empty()&&v[1].empty());
	return 0;
}