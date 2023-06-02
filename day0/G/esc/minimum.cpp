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
long long sum(int l,int r){
    if(l>r)return 0;
    return 1ll*(l+r)*(r-l+1)/2;
}
long long check(std::deque<int>& q){
    int n=q.size();
    //fprintf(stderr,"n=%d\n",n);
    std::vector<int> v;
    for(int x:q){
        v.push_back(x);
    }
    std::vector<int> op(n,-1),last(n,-1);
    for(int i=0;i<n;++i){
        if(last[v[i]]!=-1)op[i]=last[v[i]];
        last[v[i]]=i;
    }
    for(int i=0;i<n;++i){
        if(op[i]==-1){
            op[i]=last[v[i]];
        }
    }
    long long cnt=0;
    for(int L=0;L<n;++L){
        for(int R=L;R<n;++R){
            int fl=0;
            for(int i=L;i<=R;++i){
                if(op[i]>R){
                    fl=1;
                    break;
                }
            }
            if(fl)continue;
            int maxr=-1;
            for(int i=L;i<=R;++i){
                if(op[i]>i&&op[i]>maxr){
                    ++cnt;
                    maxr=op[i];
                }
            }
        }
    }
    // std::set<int, std::greater<int> > s;
    // for(int r=n-1;r>=0;--r){
    //     int l=1;
    //     if(!s.empty())l=*(s.begin())+1;
    //     cnt+=sum(1,r-l+1);
    //     if(op[r]<r)s.insert(op[r]);
    //     if(op[r]>r)s.erase(r);
    // }
    return cnt;
}
int main()
{
    int n=io::F();
    int k=n/2;
    long long max=0;
    for(int r=n/8;r<=n/8;++r){
        fprintf(stderr,"r=%d\n",r);
        for(int l=2;l<=2&&l<=r&&l+3*r<=k;++l){
            int u=k-l-r;
            std::deque<int> q;
            q.push_back(n/2+1);
            int pr=1,pl=r+1,pu=l+r+1;
            for(int i=1;i<=r;++i){
                q.push_back(pr);
                q.push_back(pu++);
                q.push_back(pu++);
                q.push_back(pr++);
            }
            while(pu<=k){
                q.push_back(pu++);
            }
            pu=l+r+1;
            for(int i=1;i<=l;++i){
                q.push_front(pl);
                q.push_front(pu++);
                q.push_front(pu++);
                q.push_front(pl++);
            }
            while(pu<=k){
                q.push_front(pu++);
            }
            q.push_front(n/2+1);
            long long cnt=check(q);
            if(cmax(max,cnt)){
                fprintf(stderr,"l=%d r=%d cnt=%lld\n",l,r,cnt);
                FILE *fp=fopen("2.in","w");
                fprintf(fp,"%d\n",n+2);
                for(int x:q){
                    fprintf(fp,"%d ",x);
                }
                fputs("",fp);
                fclose(fp);
            }
        }
    }
    // std::deque<int> q;
    // for(int i=1;i<=k;++i){
    //     q.push_back(i);
    //     q.push_back(i);
    // }
    // fprintf(stderr,"%d\n",check(q));
    return 0;
}