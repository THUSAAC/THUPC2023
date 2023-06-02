#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define Fer(i,l,r) for(int i=l;i>=r;--i)
#if 0
#define pr(...) fprintf(stderr,__VA_ARGS__)
#else
#define pr(...) void(0)
#endif

typedef long long i64;
const int maxn=1e6,maxm=1e6,maxv=1e3,N=maxn+10,M=maxm+10;
template<class T>
void alloc(T *&p,int sz){
	p=new T[sz]();
}

struct Void{
	char _[0];
	template<class T>
	friend void operator*=(T &,Void){}
	friend Void operator+(Void,Void){return Void();}
};

template<class D=Void,class M=Void>
struct MSegTree{
	struct Node{
		D d;
		M m;
		void app(const M &t){
			d*=t;
			m*=t;
		}
		void up(const Node &a,const Node &b){
			d=a.d+b.d;
			d*=m;
		}
	}*tr;
	int mx;
	int n;
	void in(int x){}
	void in(int l,int r){}
	void alloc(int n){
		for(mx=1;mx<n+2;mx<<=1);
		::alloc(tr,mx+n+3);
		this->n=n;
	}
	template<class T>
	void init(int n,T *d0){
		alloc(n);
		Fe(i,1,n)tr[mx+i].d=d0[i];
		range_update(1,n);
	}
	D &operator[](int x){
		in(x);
		return tr[mx+x].d;
	}
	void range_update(int l,int r){
		in(l),in(r);
		l+=mx,r+=mx;
		for(l>>=1,r>>=1;l<r;l>>=1,r>>=1){
			Fe(x,l,r)up(x);
		}
		for(;l;l>>=1)up(l);
	}
	void up(int x){
		tr[x].up(tr[x*2],tr[x*2+1]);
	}
	void add(int x,const D &y){//M=Void
		in(x);
		for(x+=mx;x;x>>=1)tr[x].d=tr[x].d+y;;
	}
	void update(const M &t){
		tr[1].app(t);
	}
	template<class T>
	void update(int x,T y){
		in(x);
		for(tr[x+=mx].d=y;x>1;up(x>>=1));
	}
	void update(int l,int r,const M &t){
		in(l),in(r);
		for(l+=mx-1,r+=mx+1;l^r^1;up(l>>=1),up(r>>=1)){
			if(~l&1)tr[l+1].app(t);
			if(r&1)tr[r-1].app(t);
		}
		for(;l>1;up(l>>=1));
	}
	void update_suffix(int x,const M &t){
		in(x);
		for(x+=mx-1;x>1;up(x>>=1)){
			if(~x&1)tr[x+1].app(t);
		}
	}
	D query(){
		return tr[1].d;
	}
	D query(int l,int r){
		in(l),in(r);
		D a1,a2;
		for(l+=mx-1,r+=mx+1;l^r^1;a1*=tr[l>>=1].m,a2*=tr[r>>=1].m){
			if(~l&1)a1=a1+tr[l+1].d;
			if(r&1)a2=tr[r-1].d+a2;
		}
		a1=a1+a2;
		for(;l>1;a1*=tr[l>>=1].m);
		return a1;
	}
	D query_prefix(int r){
		in(r);
		D a1;
		for(r+=mx+1;r>1;r>>=1,a1*=tr[r].m){
			if(r&1)a1=tr[r-1].d+a1;
		}
		return a1;
	}
	D query_suffix(int l){
		in(l);
		D a1;
		for(l+=mx-1;l>1;l>>=1,a1*=tr[l].m){
			if(~l&1)a1=a1+tr[l+1].d;
		}
		return a1;
	}
	void dn(int x){
		tr[x*2].app(tr[x].m);
		tr[x*2+1].app(tr[x].m);
		tr[x].m=M();
	}
	void dna(int x){
		in(x);
		x+=mx;
		for(int c=__builtin_ctz(mx);c>0;--c)dn(x>>c);
	}
	template<class T>
	int bsearch_r(int x,T f){//M=Void
		in(x);
		for(x+=mx-1;;x>>=1){
			if(~x&1){
				if(f(tr[x+1].d))break;
			}
		}
		for(++x;x<mx;){
			x<<=1;
			if(!f(tr[x].d))++x;
		}
		x-=mx;
		return x-1;
	}
	template<class T>
	int find_lm(T f){
		int x=1;
		while(x<mx){
			dn(x);
			x<<=1;
			if(!f(tr[x].d))++x;
		}
		x-=mx;
		return x;
	}
};
template<class T>
struct BIT{
	T *a;
	int n;
	void alloc(int n0){
		n=n0;
		::alloc(a,n+1);
	}
	void add(int x,T y){
		assert(1<=x&&x<=n);
		int _n=n;
		for(;x<=_n;x+=x&-x)a[x]+=y;
	}
	T sum(int x){
		assert(0<=x&&x<=n);
		T s=0;
		for(;x;x-=x&-x)s+=a[x];
		return s;
	}
	void build(){
		Fe(i,1,n){
			int j=i+(i&-i);
			if(j<=n)a[j]+=a[i];
		}
	}
};
namespace IO{
const int BUF_SZ=1<<16;
char ib[BUF_SZ+1],*ip=ib+BUF_SZ;
void ipre(int n){
	int c=ib+BUF_SZ-ip;
	if(c<n){
		memcpy(ib,ip,c);
		ip=ib;
		fread(ib+c,1,BUF_SZ-c,stdin)[ib+c]=0;
	}
}
template<class T>
T read(T L,T R){
	ipre(100);
	T x=0,f=1;
	while(*ip<'0'||*ip>'9')if(*ip++=='-')f=-f;
	while(*ip>='0'&&*ip<='9')x=x*10+*ip++-'0';
	x*=f;
	if(!(L<=x&&x<=R)){
		std::cerr<<x<<" not in ["<<L<<","<<R<<"]\n";
		exit(1);
	}
	return x;
}
char ob[BUF_SZ+1],*op=ob;
void opre(int n){
	int c=ob+BUF_SZ-op;
	if(c<n){
		fwrite(ob,1,BUF_SZ-c,stdout);
		op=ob;
	}
}
template<class T>
void write(T x){
	opre(100);
	char ss[100],*sp=ss;
	if(x<T(0))x=-x,*op++='-';
	do *sp++=x%10+'0';while(x/=10);
	while(sp!=ss)*op++=*--sp;
}
template<class T>
void write(T x,char c){
	write(x);
	*op++=c;
}
struct __{
	__(){}
	~__(){
		fwrite(ob,1,op-ob,stdout);
	}
}_;
};
using IO::read;
using IO::write;
int a[N];
const int inf=1e9;
bool is1[N],is2[N];
using std::min;
using std::max;
int n,m;
struct D1{
	int x;
	D1(int x0=inf):x(x0){}
};
struct M1{
	int x;
	M1(int x0=0):x(x0){}
};
D1 operator+(D1 a,D1 b){return D1(min(a.x,b.x));}
void operator*=(D1 &a,M1 b){a.x+=b.x;}
void operator*=(M1 &a,M1 b){a.x+=b.x;}
MSegTree<D1,M1> amnt;
MSegTree<D1> qmnt;



template<class T>
struct Sum{
	T x;
	Sum(T x0=0):x(x0){}
	operator T(){return x;}
	friend Sum operator+(Sum a,Sum b){return Sum(a.x+b.x);}
};
BIT<i64> qst,q1st;
BIT<int> q1xct;
MSegTree<Sum<int>> q1yct;
int qt(int i){
	return q1xct.sum(i)-q1yct.query_suffix(a[i]).x;
}
i64 q1s(int i){
	if(i>n)return 0;
	int n1=q1yct.query().x-q1xct.sum(i-1);
	if(!n1)return 0;
	int y=q1yct.find_lm([&n1](Sum<int> d){
		if(n1>d.x)return n1-=d.x,0;
		return 1;
	});
	i64 s=0;
	assert(q1yct[y]>=n1);
	s+=i64(n1)*y;
	if(y>1)s+=q1st.sum(y-1);
	return s;
}

int main(){
	n=read(1,maxn);
	m=read(1,maxm);
	Fe(i,1,n)a[i]=read(1,n);
	
	int mx=inf;
	Fe(i,1,n){
		if(a[i]<=mx){
			mx=a[i];
			is1[i]=1;
		}
	}
	mx=inf;
	Fe(i,1,n){
		if(a[i]<=mx&&!is1[i]){
			mx=a[i];
			is2[i]=1;
		}
	}
	
	qst.alloc(n);
	q1st.alloc(n);
	qmnt.alloc(n+1);
	q1xct.alloc(n);
	q1yct.alloc(n);
	Fe(i,1,n)if(!is1[i]){
		qst.a[i]=a[i];
		qmnt[i]=a[i];
	}else{
		q1st.a[a[i]]+=a[i];
		q1xct.a[i]+=1;
		q1yct[a[i]].x+=1;
	}
	qmnt[n+1]=0;
	qst.build();
	q1st.build();
	qmnt.range_update(1,n+1);
	q1xct.build();
	q1yct.range_update(1,n);
	
	amnt.alloc(n);
	Fe(i,1,n)if(is2[i]){
		amnt[i]=qt(i);
	}
	amnt.range_update(1,n);
	
	Fe(_,1,m){
		int y=read(1,n);
		int l=read(1,n),r=read(l,n);
		int y1=1e9;
		pr("\ny=%d\n",y);
		int y0=q1yct.find_lm([](Sum<int> d){return d.x;});
		if(y>=y0){
			q1yct.add(y,1);
			q1st.add(y,y);
			q1yct.add(y0,-1);
			q1st.add(y0,-y0);
			
			if(y>=qmnt.query().x){
				int i0=qmnt.find_lm([y](D1 d){return y>=d.x;});
				if(i0<=n)amnt.update_suffix(i0,-1);
			}
			
			mx=inf-1;
			for(;amnt.query().x==0;){
				int i=amnt.find_lm([](D1 d){return !d.x;});
				if(i>n)break;
				if(i>1)mx=min(mx,qmnt.query_prefix(i-1).x);
				
				is2[i]=0;
				is1[i]=1;
				qst.add(i,-a[i]);
				qmnt.update(i,inf);
				amnt.dna(i);
				amnt.update(i,inf);
				q1xct.add(i,1);
				q1yct.add(a[i],1);
				q1st.add(a[i],a[i]);
				for(;;){
					i=qmnt.bsearch_r(i+1,[mx](D1 d){return mx>=d.x;})+1;
					if(i>n||is2[i])break;
					mx=a[i];
					is2[i]=1;
					
					amnt.dna(i);
					amnt.update(i,qt(i));
				}
			}
		}
		i64 s=0;
		s+=q1s(l)-q1s(r+1);
		s+=qst.sum(r)-qst.sum(l-1);
		write(s,'\n');
	}
	return 0;
}
