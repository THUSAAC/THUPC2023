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
int pno;
std::pair<std::vector<int>,std::vector<int> > tree(int n){
    std::pair<std::vector<int>,std::vector<int> > ret;
    if(n==0)return ret;
    int l=n-1>>1;
    int r=n-1-l;
    auto lt=tree(l),rt=tree(r);
    int k=pno+1;
    pno+=3;
    ret.first=lt.first;
    ret.first.push_back(k);
    ret.first.push_back(k+1);
    ret.first.push_back(k+2);
    for(auto x:lt.second){
        ret.first.push_back(x);
    }
    ret.second=rt.first;
    ret.second.push_back(k+2);
    ret.second.push_back(k);
    ret.second.push_back(k+1);
    for(auto x:rt.second){
        ret.second.push_back(x);
    }
    return ret;
}
int main(){
	int n=250;
    printf("%d\n",n*6);
    auto t=tree(n);
    int k=n*3;
    for(int i=1;i<=k;++i)p[i]=i;
    for(int i=1;i<=k;++i){
        std::swap(p[i],p[R(1,i)]);
    }
    for(auto x:t.second){
        t.first.push_back(x);
    }
    for(int i=0;i<n*6;++i){
        printf("%d%c",p[t.first[i]]," \n"[i==n*6-1]);
    }
	return 0;
}