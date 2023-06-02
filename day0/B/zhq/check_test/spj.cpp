#include<bits/stdc++.h>
using namespace std;

int N , M , P[303][603] , A[303]; bool vis[603];
int ansp[603] , outp[603];

struct H{
	inline int readInt(){
		int x;
		scanf("%d",&x);
		return x;
	}
}inf,ans,ouf;

//int main(int argc, char **argv){
//	registerTestlibCmd(argc, argv);
int main(){
	for(int T=1;T<=90;T++){
		memset(A,0,sizeof(A));
		memset(P,0,sizeof(P)); 
		memset(vis,0,sizeof(vis));
		printf("case %d:   ",T);
		string S=to_string(T);
		freopen((S+".in").c_str(),"r",stdin);
		N = inf.readInt(); M = inf.readInt();
		for(int i = 1 ; i <= M ; ++i) A[i] = inf.readInt();
		for(int i = 1 ; i <= M ; ++i)
			for(int j = 1 ; j <= N ; ++j) P[i][j] = inf.readInt();
		
		freopen((S+".ans").c_str(),"r",stdin);
		for(int i = 1 ; i <= N - M ; ++i)
			ansp[i] = ans.readInt();
		
		freopen((S+".out").c_str(),"r",stdin); 
		for(int i=1;i<=N-M;i++)
			outp[i] = ouf.readInt();
		
		int p = 1;
		for(int i = 1 ; i <= N - M ; ++i){
			if(vis[outp[i]]){/*cout<<"??"<<i<<' '<<outp[i]<<endl;*/puts("Method Invalid.");}
			vis[outp[i]] = 1;
			if(A[p] == i){
				for(int x = 1 ; x <= N ; ++x)
					if(!vis[P[p][x]]){vis[P[p][x]] = 1; break;}
				++p;
			}
		}
		sort(ansp + 1 , ansp + N - M + 1);
		sort(outp + 1 , outp + N - M + 1);
		for(int i = 1 ; i <= N - M ; ++i)
			if(!(ansp[i] == outp[i]))puts("Method not Optimal.");
		puts("ok"); 
	
	}
	return 0;
}
