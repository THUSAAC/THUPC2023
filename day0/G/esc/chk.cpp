#include "testlib.h"
#include <bits/stdc++.h>

int a[2222];

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    auto out = ouf.readLine();
    auto anss = ans.readLine();
    quitif(anss == "No solution." && out == anss, _ok, "Accepted");
    quitif(anss != out, _wa, "Wrong Answer");
    int n = inf.readInt(2,1000);
    assert(n%2==0);
    for(int i=1;i<=n;++i){
        a[i]=inf.readInt(1,n/2);
    }
    int m = ouf.readInt(n,n*2);
    auto s = ouf.readToken();
    quitif(s.size()!=m, _wa, "Wrong length");
    std::vector<int> v[2];
    int now=1;
    for(char c:s){
        if(c=='0'){
            if(v[0].size()&&v[1].size()&&v[0].back()==v[1].back()){
                v[0].pop_back();
                v[1].pop_back();
            }
        }
        else if(now<=n){
            int p=c-'1';
            v[p].push_back(a[now++]);
            if(v[p].size()>=2&&v[p].back()==v[p][v[p].size()-2]){
                v[p].pop_back();
                v[p].pop_back();
            }
        }
    }
    quitif(now>n&&v[0].empty()&&v[1].empty(), _ok, "Accepted");
    quit(_wa, "Wrong Solution");
    return 0;
}
