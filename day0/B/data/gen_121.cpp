#include<bits/stdc++.h>
using namespace std;

mt19937 rnd(1345678);
int N , M , A[303] , P[303][603] , TEST_CASE = 88;

void print(){
	++TEST_CASE;
	freopen((to_string(TEST_CASE) + ".in").c_str() , "w" , stdout);
	cout << N << ' ' << M << endl;
	assert(A[1] >= 1 && A[M] < N - M);
	for(int i = 1 ; i <= M ; ++i){
		assert(i == 1 || A[i] > A[i - 1]);
		cout << A[i] << " \n"[i == M];
	}
	for(int i = 1 ; i <= M ; ++i){
		static bool vis[603]; memset(vis , 0 , sizeof(vis));
		for(int j = 1 ; j <= N ; ++j){
			cout << P[i][j] << " \n"[j == N];
			assert(P[i][j] >= 1 && P[i][j] <= N && !vis[P[i][j]]);
			vis[P[i][j]] = 1;
		}
	}
	fclose(stdout);
	system(("std.exe < " + to_string(TEST_CASE) + ".in > " + to_string(TEST_CASE) + ".ans").c_str());
	cerr << TEST_CASE << endl;
}

void random_A(){
	if(TEST_CASE % 2 == 0){M = (N - 1) / 2; for(int i = 1 ; i <= M ; ++i) A[i] = i;}
	else{
		M = rnd() % ((N - 1) / 2) + 1; vector < int > pot;
		for(int j = 1 ; j < N - M ; ++j) pot.push_back(j);
		shuffle(pot.begin() , pot.end() , rnd);
		pot.resize(M); sort(pot.begin() , pot.end());
		for(int i = 0 ; i < M ; ++i) A[i + 1] = pot[i];
	}
}

void random(int step){
	random_A();
	for(int i = 1 ; i <= M ; ++i){
		for(int j = 1 ; j <= N ; ++j) P[i][j] = j;
		
		if(!step) shuffle(P[i] + 1 , P[i] + N + 1 , rnd);
		else for(int p = 1 ; p <= step ; ++p)
			swap(P[i][rnd() % N + 1] , P[i][rnd() % N + 1]);
	}
	print();
}

void seldom_change(int t, int step){
	random_A();
	static bool vis[303]; memset(vis , 0 , sizeof(vis));
	vis[1] = 1; for(int i = 1 ; i <= t ; ++i) vis[rnd() % M + 1] = 1;
	for(int i = 1 ; i <= M ; ++i){
		if(vis[i]){
			for(int j = 1 ; j <= N ; ++j) P[i][j] = j;
			
			if(!step) shuffle(P[i] + 1 , P[i] + N + 1 , rnd);
			else for(int p = 1 ; p <= step ; ++p)
				swap(P[i][rnd() % N + 1] , P[i][rnd() % N + 1]);
		}else memcpy(P[i] , P[i - 1] , sizeof(P[i]));
	}
	print();
}

void choose_in_random(int size , int step){
	random_A();
	vector < vector < int > > pot;
	for(int i = 1 ; i <= size ; ++i){
		vector < int > seq;
		for(int j = 1 ; j <= N ; ++j) seq.push_back(j);
		if(!step) shuffle(seq.begin() , seq.end() , rnd);
		else for(int i = 1 ; i <= step ; ++i)
			swap(seq[rnd() % N] , seq[rnd() % N]);
		pot.push_back(seq);
	}
	for(int i = 1 ; i <= M ; ++i){
		vector < int > seq = pot[rnd() % size];
		for(int j = 0 ; j < N ; ++j) P[i][j + 1] = seq[j];
	}
	print();
}

int gen(int l , int r){return rnd() % (r - l + 1) + l;}

void slow_modified(bool flag){
	auto fill = [&](int i , int p){
		int pos = p;
		for(int j = 1 ; j <= N ; ++j)
			if(find(P[i] + 1 , P[i] + p + 1 , j) == P[i] + p + 1) 
				P[i][++pos] = j;
		if(flag) shuffle(P[i] + p + 1 , P[i] + N + 1 , rnd);
		else reverse(P[i] + p + 1 , P[i] + N + 1);
	};
	M = max(1 , N / 2 - (int)(rnd() % 3) - 1); for(int i = 1 ; i <= M ; ++i) A[i] = i;
	int h = M / 2;
	for(int i = 1 ; i <= M - h ; ++i){
		P[i][1] = M + i; P[i][2] = gen(P[i][1] + 1 , 2 * M - h + (i == M - h));
		fill(i , 2);
	}
	for(int i = M - h + 1 ; i <= M ; ++i){
		vector < int > pot; pot.push_back(M + i); pot.push_back(M + i - 1);
		for(int j = 1 ; j <= M - (M - i) ; ++j)
			pot.push_back(j);
		shuffle(pot.begin() + 2 , pot.end() , rnd);
		pot.push_back(M + i + 1);
		for(int j = 0 ; j < pot.size() ; ++j)
			P[i][j + 1] = pot[j];
		fill(i , pot.size());
	}
	print();
}


int main(){
	N = 600; slow_modified(0); slow_modified(1);

	return 0;
}