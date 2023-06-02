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
const int maxm=2004;
int a[maxm];
int op[maxm];
int last[maxm];
int f[maxm][maxm][2];
int s[maxm][maxm][2];
int ly[maxm][maxm];
const int inf=351493;
int to[maxm];
int rr[maxm];
int xcnt[maxm],xl[maxm];
#define BOTH 0
int formid, visit;
void dfs(int l,int r,int t,int offset){
	if(l>r)return;
	if(ly[l][r]<=r){
		to[ly[l][r]]=t^offset;
		dfs(l,ly[l][r]-1,t^1,offset);
		dfs(ly[l][r]+1,r,1,offset^t^1);
	}
	else{
		if(s[l][r][t]<0){
			to[-s[l][r][t]]=offset^1;
			dfs(l,-s[l][r][t]-1,0,offset);
			dfs(-s[l][r][t]+1,r,BOTH,offset);
		}
		else{
			to[s[l][r][t]]=offset;
			to[op[s[l][r][t]]]=offset^1;
			if(s[l][r][t]<op[s[l][r][t]]){
				dfs(l,s[l][r][t]-1,1,offset);
				dfs(s[l][r][t]+1,op[s[l][r][t]]-1,1,offset^1);
				dfs(op[s[l][r][t]]+1,r,BOTH,offset);
			}
			else{
				dfs(l,op[s[l][r][t]]-1,0,offset);
				dfs(op[s[l][r][t]]+1,s[l][r][t]-1,1,offset);
				dfs(s[l][r][t]+1,r,BOTH,offset^1);
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
int query(int p){
	int ret=inf;
	for(int i=p;i<maxm;i+=i&-i){
		cmin(ret,min[i]);
	}
	return ret;
}
int main()
{
	int m=io::F();
	for(int i=1;i<=m;++i){
		a[i]=io::F();
		if(last[a[i]])op[i]=last[a[i]];
		last[a[i]]=i;
	}
	for(int i=1;i<=m;++i){
		if(!op[i]){
			op[i]=last[a[i]];
		}
	}
	for(int r=m;r;--r){
		ly[r+1][r]=m+1;
		for(int l=r;l;--l){
			ly[l][r]=ly[l+1][r];
			if(op[l]>r){
				ly[l][r]=l;
			}
		}
	}
	for(int l=m;l;--l){
		int rx=0;
		xcnt[l-1]=0;
		xl[l-1]=l;
		for(int r=l;r<=m;++r){
			xcnt[r]=xcnt[r-1]+op[r]<l;
			xl[r]=xl[r-1];
			if(op[r]<l){
				cmin(xl[r],op[r]);
			}
		}
		memset(min,63,sizeof(min));
		for(int r=m;r>=l;--r){
			rr[r]=query(xl[r]);
			if(op[r]<l){
				insert(op[r],r);
			}
		}
		
		for(int r=l;r<=m;++r){
			if(op[r]<l){
				rx=r;
			}
			if(ly[l][r]>r){
				f[l][r][0]=inf;
				int rmax=l;
				for(int k=l;k<=r;++k){
					++formid;
					if(op[k]>rmax){
						++visit;
						if(rx<k){
							int left=f[l][k-1][1];
							int mid=1+f[k+1][op[k]-1][1];
							int right=2+f[op[k]+1][r][BOTH];
							int tmp=dmax(left,mid);
							cmax(tmp,right);
							if(cmin(f[l][r][0],tmp)){
								s[l][r][0]=k;
							}
						}
						if(xl[k]==l||r<rr[k]&&rx<op[k]){
							int left=xcnt[r]-xcnt[k]+f[l][k-1][0];
							int mid=1+f[k+1][op[k]-1][1];
							int right=2+f[op[k]+1][r][BOTH];
							int tmp=dmax(left,mid);
							cmax(tmp,right);
							if(cmin(f[l][r][0],tmp)){
								s[l][r][0]=op[k];
							}
						}
						rmax=op[k];
					}
				}
				if(xl[r]!=l){
					int xlp=op[xl[r]];
					if(xl[xlp-1]==l||r<rr[xlp-1]){
						int tmp=dmax(xcnt[r]-xcnt[xlp-1]+f[l][xlp-1][0],2+f[xlp+1][r][BOTH]);
						if(cmin(f[l][r][0],tmp)){
							s[l][r][0]=-xlp;
						}
					}
				}
				f[l][r][1]=f[l][r][0];
				s[l][r][1]=s[l][r][0];
			}
			else{
				f[l][r][0]=f[l][r][1]=inf;
				int ly=::ly[l][r];
				if(rx<ly){
					f[l][r][0]=dmax(f[l][ly-1][1],1+f[ly+1][r][1]);
				}
				if(xl[ly]==l||r<rr[ly]){
					f[l][r][1]=dmax(xcnt[r]-xcnt[ly]+f[l][ly-1][0],1+f[ly+1][r][1]);
				}
			}
		}
	}
	fprintf(stderr,"formid=%d visit=%d\n",formid,visit);
	if(f[1][m][BOTH]==inf){
		puts("No solution.");
		return 0;
	}
	puts("Cleared.");
	printf("%d\n",m*3/2);
	dfs(1,m,BOTH,0);
	std::vector<int> v[2];
	for(int i=1;i<=m;++i){
		putchar('1'+to[i]);
		v[to[i]].push_back(a[i]);
		while(v[0].size()&&v[1].size()&&v[0].back()==v[1].back()){
			putchar('0');
			v[0].pop_back();
			v[1].pop_back();
		}
	}
	puts("");
	assert(v[0].empty()&&v[1].empty());
	return 0;
}