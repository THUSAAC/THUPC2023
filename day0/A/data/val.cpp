#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
using namespace std;
inline li read(li l = 0,li r = 1e9){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9'){
		assert(y != '-' && (c == ' ' || c == '\n' || c == '\r' || c == '-'));
		y = c;c = gc;
	} 
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	assert(c == -1 || c == ' ' || c == '\n' || c == '\r');
	if(y == '-') x *= -1;
	assert(x >= l && x <= r);
	return x;
}
void end_chk(){
	char c;
	do{
		c = gc;
		assert(c == -1 || c == ' ' || c == '\n' || c == '\r');			
	}while(c != -1);
}
int n,m,k,s;
int main(){
	int tot = 40;
	for(int tsd = 1;tsd <= tot;++tsd){
		cerr<<tsd<<":"<<endl;
		char ch[50];
		sprintf(ch,"%d.in",tsd);
		freopen(ch,"r",stdin);
		k = read(1,17);n = 1 << k;
		m = read(1,200000);s = read(0,n - 1);
		for(int i = 1;i <= k;++i) read(0,(1 << 30) - 1);
		for(int i = 1;i <= m;++i){
			read(0,n - 1);read(0,n - 1);read(0,(1 << 30) - 1);
		}
		end_chk();
		fclose(stdin); 
		freopen("con","r",stdin);
		//sprintf(ch,"std.exe <%d.in >a.out",tsd);
		//system(ch);
		//sprintf(ch,"fc %d.ans a.out",tsd);
		//system(ch);
		sprintf(ch,"a.exe <%d.in >a.out",tsd);
		system(ch);
		sprintf(ch,"fc %d.ans a.out",tsd);
		system(ch);
		//sprintf(ch,"brute.exe <%d.in >a.out",tsd);
		//system(ch);
		//sprintf(ch,"fc %d.ans a.out",tsd);
		//system(ch);
	} 
	return 0;
}
