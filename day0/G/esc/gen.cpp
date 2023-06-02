#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io{
	int F(){
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G(){
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
std::mt19937_64 gen(std::random_device{}());
int R(int l, int r){
    return std::uniform_int_distribution<>(l,r)(gen);
}
unsigned long long h[2222];
int p[1111];
std::vector<int> a,ops;
std::map<unsigned long long, int> m;
int main(){
	//int n=R(725,750)*2;
    //int n=16;
    int n=748*2;
    int k=n/2;
    for(int i=1;i<=k;++i)p[i]=i;
    for(int i=1;i<=k;++i){
        std::swap(p[i],p[R(1,i)]);
    }
    for(int i=1;i<=k;++i)h[i]=gen();
    std::vector<int> v[2];
    int now=1;
    unsigned long long sum=0;
    m[0]=1;
    int ccnt=0;
    for(int i=1;i<=250;++i)ops.push_back(0);
    ops.push_back(2);
    for(int i=1;i<=10;++i){
        ops.push_back(0);
        ops.push_back(1);
        ops.push_back(1);
    }
    ops.push_back(1);
    for(int i=1;i<=n+k;++i){
        int op,cnt=0;
        do{
            op=R(0,2);
            ++cnt;
        }
        while(op==0&&now>k||op==1&&v[0].empty()||op==2&&v[1].empty()||op==1&&cnt<=1000&&m.count(sum^h[v[0].back()])||op==2&&cnt<=1000&&m.count(sum^h[v[1].back()])||op==1&&cnt<=100&&a.size()>=2&&v[0].back()==a[a.size()-2]||op==2&&cnt<=100&&a.size()>=2&&v[1].back()==a[a.size()-2]);
        if(cnt>100)++ccnt;
        op=ops[i-1];
        if(op==0){
            v[0].push_back(now);
            v[1].push_back(now++);
        }
        if(op==1){
            a.push_back(v[0].back());
            sum^=h[v[0].back()];
            m[sum]=1;
            v[0].pop_back();
        }
        if(op==2){
            a.push_back(v[1].back());
            sum^=h[v[1].back()];
            m[sum]=1;
            v[1].pop_back();
        }
    }
    int l=R(n/2-10,n/2+10);
    int r=R(n/2-10,n/2+10);
    //std::swap(a[l],a[r]);
    printf("%d\n",n);
    for(int i=n-1;i>=0;--i){
        printf("%d%c",p[a[i]]," \n"[i==0]);
    }
    fprintf(stderr,"ccnt=%d\n",ccnt);
	return 0;
}