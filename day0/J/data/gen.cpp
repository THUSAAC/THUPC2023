#include<bits/stdc++.h>
using namespace std;

#define int long long
const int _ = 1e5 + 7; int N;
mt19937 rnd(123456); ofstream log_stream;
struct dat{
	vector < int > fa , A; int N; bool wrong;
	dat(int _n){N = _n; fa.resize(_n + 2); A.resize(_n + 2); wrong = 0;}
	void print(){
		cout << N << endl;
		vector < int > perm , rev(N + 1); for(int i = 1 ; i <= N ; ++i) perm.push_back(i);
		shuffle(perm.begin() + 1 , perm.end() , rnd); perm.insert(perm.begin() , 0);
		for(int i = 1 ; i <= N ; ++i) rev[perm[i]] = i;
		for(int i = 1 ; i <= N ; ++i) cout << A[rev[i]] << " \n"[i == N];
		for(int i = 2 ; i <= N ; ++i) cout << perm[fa[i]] << ' ' << perm[i] << '\n';

		int sum = 0; for(int i = 2 ; i <= N ; ++i) sum += A[i] != -1;
		log_stream << N << " " << sum << " " << (set < int > (fa.begin() + 2 , fa.begin() + N + 1).size()) << " " << wrong << endl;
	}
}; vector < dat > allCase; int testcase = 1;
int gen(int l = 0 , int r = 1e9){return l + (int)(rnd() % (r - l + 1));}
bool gen(double prob){return rnd() < UINT_MAX * prob;}
int gen_distribution(vector < int > &cdf){int T = rnd() % cdf.back(); return upper_bound(cdf.begin() , cdf.end() , T) - cdf.begin();}
int gen_distribution_clip(vector < int > &cdf , int len){
	int pos = min(len , (int)cdf.size() - 1);
	int T = rnd() % cdf[pos]; return upper_bound(cdf.begin() , cdf.end() , T) - cdf.begin();
}

void print(){
	freopen((to_string(testcase) + ".in").c_str() , "w" , stdout);
	log_stream = ofstream(to_string(testcase) + ".log");
	cout << allCase.size() << endl; for(auto t : allCase) t.print();
	fclose(stdout); allCase.clear(); cerr << testcase << endl;
	system(("std.exe < " + to_string(testcase) + ".in > " + to_string(testcase) + ".ans").c_str());
	++testcase;
}

void special1(int dlt){
	dat cur(N = 65535); for(int i = 2 ; i <= N ; ++i) cur.fa[i] = i / 2;
	for(int i = 1 ; i <= N ; ++i) cur.A[i] = i * 2 > N ? 1e9 : -1;
	cur.A[dlt] = 1e9; cur.wrong = dlt; allCase.push_back(cur); 
}

void special2(int dlt){
	dat cur(N = 65535); for(int i = 2 ; i <= N ; ++i) cur.fa[i] = i / 2;
	for(int i = 1 ; i <= N ; ++i) cur.A[i] = i == 1 ? 14 + dlt : -1;
	cur.wrong = !dlt; allCase.push_back(cur);
}

void special3(double prob){
	dat cur(N = 99999); for(int i = 2 ; i <= N ; ++i) cur.fa[i] = i - (i % 2) - 1;
	for(int i = N ; i ; --i){int tarval = (N - i) / 2; if(i == 1 || gen(prob)) cur.A[i] = tarval; else cur.A[i] = -1;}
	allCase.push_back(cur);
}

void gen2(){
	dat cur(N = 2); cur.fa[2] = 1; bool f = gen(0 , 1);
	if(gen(0.5)){int t = gen(1 , 2); cur.A[t] = -1; cur.A[3 - t] = gen(0.99) ? gen() : -1;}
	else{
		int p = gen(1ll) - 1; cur.A[1] = p; 
		cur.A[2] = f ? p : (gen(0.5) ? max(p + 2 * gen(0 , 1) - 1 , 0ll) : gen());
	}
	cur.wrong = f; allCase.push_back(cur);
}

void gen3(){
	dat cur(N = 3); bool f = gen(0 , 1);
	if(gen(0.5)){
		if(gen(0.5)) cur.fa[cur.fa[3] = 2] = 1; else cur.fa[cur.fa[2] = 3] = 1;
		int p = gen(); 
		for(int i = 1 ; i <= 3 ; ++i) cur.A[i] = gen(0.67) ? (f ? gen() : p) : -1;
	}else{
		cur.fa[2] = cur.fa[3] = 1;
		if(gen(0.5)){
			//max
			int p = gen(1 , 1e9 - 1) , q = gen(0 , p) , t = gen(2 , 3); cur.A[1] = cur.A[t] = p; cur.A[5 - t] = q;
			for(int i = 1 ; i <= 3 ; ++i) if(gen(0.33)) cur.A[i] = -1;
			if(f) cur.A[t] = gen(p + 1);
		}else{
			//max+1
			int p = gen(0 , 1e9 - 1); cur.A[2] = cur.A[3] = p; cur.A[1] = p + 1;
			for(int i = 1 ; i <= 3 ; ++i) if(gen(0.33)) cur.A[i] = -1;
			if(f) cur.A[1] = gen(0 , p);
		}
	}
	allCase.push_back(cur);
}

double reveal_prob , maxp1_prob; vector < int > weight_distribution , chnum_distribution;

pair < int , int > down_top(dat &D , vector < int > spare_vertex , int target_vertex){
	shuffle(spare_vertex.begin() , spare_vertex.end() , rnd);
	vector < int > val{-1 , -1}; bool f = 0;

	if(spare_vertex.size()){
		vector < int > child , weight; vector < vector < int > > pot;
		int cnt = gen_distribution_clip(chnum_distribution , spare_vertex.size());
		for(int i = 1 ; i <= cnt ; ++i){
			int t = spare_vertex.back(); child.push_back(t);
			spare_vertex.pop_back(); D.fa[t] = target_vertex;
			pot.push_back({});
			weight.push_back(gen_distribution(weight_distribution));
		}
		partial_sum(weight.begin() , weight.end() , weight.begin());
		for(auto t : spare_vertex) pot[gen_distribution(weight)].push_back(t);
		for(int i = 0 ; i < cnt ; ++i){
			pair < int , int > ans = down_top(D , pot[i] , child[i]);
			val.push_back(ans.first); f |= ans.second;
		}
	}else f = 1;
	sort(val.begin() , val.end());
	int mx = val.back() + (val[val.size() - 2] == val.back());
	if(gen(reveal_prob)){
		if(gen(1.2 / reveal_prob / D.N) && mx > 0){
			D.A[target_vertex] = (f ? max(0ll , mx - gen(1 , 3)) : max(0ll , mx + (gen(0 , 1) * 2 - 1) * gen(1 , 3)));
			D.wrong = 1;
		}else D.A[target_vertex] = mx + (f ? gen(0 , 2) : 0);
		return make_pair(D.A[target_vertex] , 0);
	}else{D.A[target_vertex] = -1; return make_pair(mx , f);}
}

void top_down(dat &D , vector < int > spare_vertex , int target_vertex , pair < int , int > target_value){
	shuffle(spare_vertex.begin() , spare_vertex.end() , rnd);
	if(spare_vertex.size() == 1){
		int t = spare_vertex[0]; D.fa[t] = target_vertex;
		if(target_value.first > 0 && target_value.second == 1){D.A[target_vertex] = -1; D.A[t] = target_value.first;}
		else if(target_value.second == 0){
			D.A[target_vertex] = target_value.first;
			if(gen(1.2 / reveal_prob / D.N)){D.A[t] = gen(target_value.first + 1 , 1e9); D.wrong = 1;}
			else D.A[t] = gen(reveal_prob) ? target_value.first : -1;
		}else{D.A[target_vertex] = D.A[t] = -1;}
		return;
	}
	if(spare_vertex.size() == 0){
		assert(!target_value.first || !target_value.second); 
		D.A[target_vertex] = target_value.second ? -1 : target_value.first;
		return;
	}
	
	D.A[target_vertex] = target_value.second == 0 && gen(reveal_prob) ? target_value.first : -1;
	if(D.A[target_vertex] != -1 && gen(0.5)){
		target_value.second = 1;
		bool f = gen(1.2 / reveal_prob / D.N * 2);
		if(f){target_value.first = target_value.first + gen(1 , 3); D.wrong = 1;}
		else{target_value.first = (gen(0.85) ? max(target_value.first - gen(0 , 2) , 0ll) : gen(0 , target_value.first));}
	}

	vector < int > child , target_val , target_label , weight; vector < vector < int > > pot;
	int cnt = gen_distribution_clip(chnum_distribution , target_value.first == 0 ? 1 : spare_vertex.size() - target_value.second);
	for(int i = 1 ; i <= cnt ; ++i){
		int t = spare_vertex.back(); child.push_back(t);
		spare_vertex.pop_back(); D.fa[t] = target_vertex;
		pot.push_back({}); target_label.push_back(0);
		weight.push_back(gen_distribution(weight_distribution));
	}
	if(target_value.second == 1){
		bool f = 0; 
		while(!f) 
			for(int i = 0 ; i < cnt ; ++i) 
				if(gen(1.0 / cnt) && spare_vertex.size()){
					f = 1; target_label[i] = 1;
					pot[i].push_back(spare_vertex.back()); spare_vertex.pop_back();
				}
	}
	partial_sum(weight.begin() , weight.end() , weight.begin());
	for(auto t : spare_vertex) pot[gen_distribution(weight)].push_back(t);
	if(child.size() == 1) target_val.push_back(target_value.first);
	else{
		if(gen(maxp1_prob)){target_val.push_back(target_value.first - 1); target_val.push_back(target_value.first - 1);}
		else target_val.push_back(target_value.first);
		while(target_val.size() < child.size())
			 target_val.push_back(gen(0.9) ? max(target_value.first - gen(1 , 4) , 0ll) : gen(0 , target_value.first - 1));
	}
	shuffle(target_val.begin() , target_val.end() , rnd);
	for(int i = 0 ; i < cnt ; ++i)
		top_down(D , pot[i] , child[i] , make_pair(target_val[i] , target_label[i]));
}

struct distribution_maker{
	vector < int > exponential_decay(int len , double pw , int clip , int stepsize){
		vector < int > tot(len); double cur = pw;
		for(int i = len - 1 ; i >= 0 ; i -= stepsize){tot[i] = ceil(cur); cur = min(cur * pw , clip - 1e-9);}
		partial_sum(tot.begin() , tot.end() , tot.begin()); return tot;
	}
	vector < int > linear_decay(int len , double val , int clip , int stepsize){
		vector < int > tot(len); double cur = 0.01;
		for(int i = len - 1 ; i >= 0 ; i -= stepsize){tot[i] = ceil(cur); cur = min(cur + val , clip - 1e-9);}
		partial_sum(tot.begin() , tot.end() , tot.begin()); return tot;
	}
	vector < int > random_select(int len , int num_sample){
		vector < int > tot(len); for(int i = 0 ; i < num_sample ; ++i) ++tot[gen(0 , len - 1)];
		partial_sum(tot.begin() , tot.end() , tot.begin()); return tot;
	}
	vector < int > generate_distribution(int len){
		vector < int > dis;
		switch(gen(0 , 2)){
			case 0:
				dis = exponential_decay(len , 1 + gen(0 , 10) / 100.0 , 5 * len , gen(1 , (int)ceil(sqrt(len))));
				break;
			case 1:
				dis = linear_decay(len , gen(10 , 50) / 100.0 , 5 * len , gen(1 , (int)ceil(sqrt(len))));
				break;
			case 2:
				dis = random_select(len , gen((int)pow(len , 0.4) , (int)pow(len , 0.9)));
				break;
		}
		for(auto &t : dis) ++t;
		dis.insert(dis.begin() , 0); return dis;
	}
}Distribution_Maker;

void gen_general(double down_top_prob, int cntcase , int total , double small_prob){
	vector < int > pot(cntcase , 2); total -= cntcase * 2;
	vector < int > distribution;
	for(int i = 1 ; i <= cntcase ; ++i) distribution.push_back(gen(1 , min(cntcase , 3000ll)));
	partial_sum(distribution.begin() , distribution.end() , distribution.begin());
	for(int i = 1 ; i <= total ; ++i){
		int t = gen_distribution(distribution);
		while(pot[t] == 1e5) t = gen_distribution(distribution);
		++pot[t];
	}
	for(int i = 0 ; i < cntcase ; ++i){
		dat cur(pot[i]); vector < int > spare_vertex;
		for(int j = 2 ; j <= pot[i] ; ++j) spare_vertex.push_back(j);
		N = pot[i]; 
		reveal_prob = gen(1 , N) * 1.0 / N; 
		//reveal_prob = 1.0;
		maxp1_prob = gen(1 , N) * 1.0 / N;
		weight_distribution = Distribution_Maker.generate_distribution(gen(2 , pot[i]));
		chnum_distribution = Distribution_Maker.generate_distribution(gen(2 , max(2ll, min(pot[i] , gen(0.67) ? 20 : (int)pow(pot[i] , 0.7)))));
		if(gen(down_top_prob)) down_top(cur , spare_vertex , 1);
		else top_down(cur , spare_vertex , 1 , make_pair(gen(small_prob) ? gen(0 , 20) : gen(1 , 1e9 - 1) , gen(0 , 1)));
		allCase.push_back(cur);
	}
	print();
}

signed main(){
	special1(0); special2(0); print();
	special1(1); special2(1); print();
	special3(0.001); special3(0.5); print();
	for(int i = 1 ; i <= 1e5 ; ++i) gen2();
	print();
	for(int i = 1 ; i <= 66666 ; ++i) gen3();
	print();
	gen_general(0.5 , 5e4 , 2e5 , 0.5);
	gen_general(0.5 , 2e4 , 2e5 , 0.5);
	gen_general(0.5 , 5000 , 2e5 , 0.5);
	gen_general(0.5 , 2000 , 2e5 , 0.5);
	gen_general(0.5 , 500 , 2e5 , 0.5);
	gen_general(0.5 , 200 , 2e5 , 0.5);
	gen_general(0.5 , 50 , 2e5 , 0.5);
	gen_general(0.5 , 20 , 2e5 , 0.5);
	gen_general(0.5 , 8 , 2e5 , 0.5);
	gen_general(0.5 , 4 , 2e5 , 0.5);
	gen_general(0.5 , 2 , 2e5 , 0.5);

	return 0;
}