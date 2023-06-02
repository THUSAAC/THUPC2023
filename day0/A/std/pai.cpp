//Love and Freedom.
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define inf 20021225
using namespace std;
int read()
{
    int s=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')    f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9')    s=s*10+ch-'0',ch=getchar();
    return s*f;
}
int main()
{
	while(1)
	{
		system("data.exe");
		system("brute.exe<in.txt>ans.txt");
		system("lily.exe<in.txt>out.txt");
		if(system("fc ans.txt out.txt"))	break;
	}
	return 0;
}

