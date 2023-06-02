#include<bits/stdc++.h>
using namespace std;

mt19937 rnd(1); 
bool gen(double p){return rnd() < UINT_MAX * p;}
int gen(int l = 1 , int r = 10000){return rnd() % (r - l + 1) + l;}

int TEST_CASE; 
void start_test_case(){++TEST_CASE; freopen((to_string(TEST_CASE) + ".in").c_str() , "w" , stdout);}
void end_test_case(){
	fclose(stdout); system(("std.exe < " + to_string(TEST_CASE) + ".in > " + to_string(TEST_CASE) + ".ans").c_str());
	cerr << "Case " << TEST_CASE << " Complete" << endl;
}

void random_sample(int L , double p){
	vector < string > pot;
	while(pot.empty())
		for(int i = 0 ; i < 1 << L ; ++i)
			if(gen(p)){string str; for(int j = 0 ; j < L ; ++j){str.push_back('0' + (i >> j & 1));} pot.push_back(str);}
	cout << L << ' ' << pot.size() << endl;
	for(int i = 1 ; i <= L ; ++i) cout << gen() << " \n"[i == L];
	for(auto t : pot) cout << t << "\n";
}

void random_sample(int T , int L , double basep , double step){
	start_test_case();
	cout << T << endl; while(T--){random_sample(L == -1 ? gen(1 , 15) : L , basep); basep += step;}
	end_test_case();
}

void same1(int L , int D , double p){
	vector < string > str , pot;
	for(int i = 0 ; i < 1 << L ; ++i){
		string s; int cnt = 0;
		for(int j = 0 ; j < L ; ++j){cnt += i >> j & 1; s.push_back('0' + (i >> j & 1));}
		if(cnt == D || cnt == L - D) str.push_back(s);
	}
	while(pot.empty()) for(auto s : str) if(gen(p)) pot.push_back(s);
	cout << L << ' ' << pot.size() << endl;
	for(int i = 1 ; i <= L ; ++i) cout << gen() << " \n"[i == L];
	for(auto t : pot) cout << t << "\n";
}

void same1(int T , int L , int D , double p){
	start_test_case();
	cout << T << endl;
	for(int i = 1 ; i <= T ; ++i){
		int cL = L == -1 ? gen(1 , 15) : L;
		same1(cL , D == -1 ? gen(0 , cL) : D , p == -1 ? gen(90 , 100) / 100.0 : p);
	}
	end_test_case();
}

void special_random_sample(int L, double p, double p1){
	vector < string > pot;
	while(pot.empty())
		for(int i = 0 ; i < 1 << L ; ++i)
			if(gen(p)){string str; for(int j = 0 ; j < L ; ++j){str.push_back('0' + (i >> j & 1));} pot.push_back(str);}
	cout << L << ' ' << pot.size() << endl;
	for(int i = 1 ; i <= L ; ++i) cout << (gen(p1) ? 10000 : gen()) << " \n"[i == L];
	for(auto t : pot) cout << t << "\n";
}

void special_random_sample(int T){
	start_test_case(); double basep = 0, step = 1.0 / 9;
	cout << T << endl; while(T--){special_random_sample(gen(1 , 15) , 0.5, basep); basep += step;}
	end_test_case();
}

void maximum_input(int T){
	start_test_case();
	cout << T << endl;
	while(T--){
		cout << "15 32768\n";
		for(int i = 1 ; i <= 15 ; ++i) cout << gen() << " \n"[i == 15];
		for(int i = 0 ; i < 1 << 15 ; ++i, cout << '\n')
			for(int j = 0 ; j < 15 ; ++j) cout << (i >> j & 1);
	}
	end_test_case();
}

int main(){
	random_sample(10 , 15 , 0.02 , 0.001);
	random_sample(10 , 15 , 0.03 , 0.001);
	random_sample(10 , 15 , 0.05 , 0.001);
	random_sample(10 , 15 , 0.1 , 0.01);
	random_sample(10 , 15 , 0.2 , 0.02);
	random_sample(10 , 15 , 0.5 , 0.03);
	random_sample(10 , 15 , 0.001 , 0.1);
	random_sample(10 , 15 , 0.1 , 0.1);
	random_sample(10 , -1 , 0.1 , 0.01);
	random_sample(10 , -1 , 0.02 , 0.001);
	random_sample(10 , -1 , 0.5 , 0.05);
	same1(10 , 15 , 11 , 0.99);
	same1(10 , 15 , 11 , 0.85);
	same1(10 , 15 , 9 , 0.98);
	same1(10 , 15 , 8 , 0.97);
	same1(10 , 15 , 12 , 0.95);
	same1(10 , -1 , -1 , -1);
	same1(10 , -1 , -1 , -1);
	special_random_sample(10);
	special_random_sample(10);
	maximum_input(10);

	return 0;
}