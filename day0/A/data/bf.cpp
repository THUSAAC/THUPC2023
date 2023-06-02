#include<bits/stdc++.h>
//#pragma gcc optimize(3)
#define gc getchar()
//char buf[100000],*buff = buf + 100000;
//#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define pc putchar
//char bfu[10000000],*bfuu = bfu;
//#define pc(x) (*(bfuu++) = x)
#define li long long
#define uli unsigned li
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define md int mid = l + r >> 1
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
using namespace std;
//const int mo = 998244353;
//const int mo = 1000000007;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
inline void file(char *s){
	char c[50];
	sprintf(c,"%s.in",s);
	freopen(c,"r",stdin);
	sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int k,n,m,s,a[20],dis[50000010];
priority_queue<pii> q;
struct edge{
	int to,nxt,val;
}e[400010];
int cnt,fir[50000010];
inline void ins(int u,int v,int w){
	//cerr<<u<<" "<<v<<" "<<w<<"()"<<endl;
	e[++cnt].to = v;e[cnt].nxt = fir[u];fir[u] = cnt;e[cnt].val = w;
	e[++cnt].to = u;e[cnt].nxt = fir[v];fir[v] = cnt;e[cnt].val = w;
} 
#define node(x,y,z) ((z) * k * n + (y) * n + (x))
#define getx(id) ((id) & (n - 1))
#define gety(id) (((id) >> k) % k)
#define getz(id) (((id) >> k) / k)
inline void ud(int to,int val){
	//cerr<<to<<" "<<val<<"***"<<endl;
	if(dis[to] > val){
		dis[to] = val;
		q.push(mp(-val,to));
	}
}
int main(){
	srand(time(0));rd();
	//file("");
	int i,j,u,v,w;
	k = read();n = 1 << k;m = read();s = read();
	for(i = 1;i <= k;++i) a[i] = read();
	for(i = 1;i <= m;++i){
		u = read();v = read();w = read();
		ins(u,v,w);
	}
	memset(dis,0x3f,sizeof(dis));dis[node(s,0,0)] = 0;
	q.push(mp(0,node(s,0,0)));
	while(!q.empty()){
		pii p = q.top();q.pop();
		if(dis[p.se] != -p.fi) continue;
		int x = getx(p.se),y = gety(p.se),z = getz(p.se);
		//cerr<<x<<" "<<y<<" "<<z<<":"<<-p.fi<<endl;
		if(y == 0 && z == 0){
			for(i = fir[x];i;i = e[i].nxt){
				ud(node(e[i].to,0,0),e[i].val - p.fi);
			}
		}
		int nxt = x ^ (1 << y);
		if(y == k - 1){
			ud(node(x,0,0),a[z] - p.fi);
			ud(node(nxt,0,0),a[z + 1] - p.fi);
		}
		else{
			ud(node(x,y + 1,z),-p.fi);
			ud(node(nxt,y + 1,z + 1),-p.fi);
		}
	}
	for(i = 0;i < n;++i) print(dis[node(i,0,0)]),pc(' ');
	pc('\n');
	//fwrite(bfu,1,bfuu - bfu,stdout);
	cerr<<clock()<<endl;
	return 0;
}


