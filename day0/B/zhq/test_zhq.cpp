#include<bits/stdc++.h>
using namespace std;

const int MAXN=660;
int n,m;
int a[MAXN];
int p[MAXN][MAXN];
bool is_chosen[MAXN];
bool vis[MAXN];
vector<int>lst;

bool ch_ck(){
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
				if(vis[x]==true)continue;
				else{
					vis[x]=true;
					break;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){ 
		if(is_chosen[i]==true&&vis[i]==false){
			lst.push_back(i);
		}
	}
	return true;
}

int main(){
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
}
