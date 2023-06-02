#include<bits/stdc++.h>
using namespace std;

const int MAXN=660;
int n,m;
int a[MAXN];
int p[MAXN][MAXN];
bool is_chosen[MAXN];
bool vis[MAXN];//已经放进去了 
vector<int>lst;

bool ch_ck(){
//	puts("---------");
	lst.clear();
	memset(vis,false,sizeof(vis));
	int occu=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			int x=p[i][j];
			if(is_chosen[x]==true){
				if(vis[x]==false){
					vis[x]=true;
					occu++;lst.push_back(x);
					if(occu>a[i])return false;
				}
			}else{
//				cout<<"?"<<x<<endl;
				if(vis[x]==true)continue;
				else{
					vis[x]=true;//牺牲了/kel 
					break;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){//该牺牲的都牺牲了。 
		if(is_chosen[i]==true&&vis[i]==false){
			lst.push_back(i);
//			cout<<"???"<<i<<endl;
//			for(int j=0;j<lst.size();j++)printf("%d ",lst[j]);puts("");
		}
	}
	return true;
}

int main(){
	for(int T=1;T<=90;T++){
		memset(is_chosen,0,sizeof(is_chosen));
		string S=to_string(T);
		freopen((S+".in").c_str(),"r",stdin);
		freopen((S+".out").c_str(),"w",stdout); 
//		freopen("hh.in","r",stdin);
		
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)scanf("%d",&a[i]);
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++)scanf("%d",&p[i][j]);
		}
		for(int i=1;i<=n;i++){
			is_chosen[i]=true; 
			if(!ch_ck())is_chosen[i]=false;
		}
		ch_ck();
		for(int i=0;i<lst.size();i++)printf("%d ",lst[i]);puts("");
		
		fclose(stdin);
		fclose(stdout);
	}
}
