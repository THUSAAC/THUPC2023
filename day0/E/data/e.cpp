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
#define db long double
//队伍种类
#define SOUTH 0
#define NORTH 1
string team_name[2] = {"South","North"};
//种族种类
#define WEAK 0
#define AVERAGE 1
#define STRONG 2
string skill_name[3] = {"Weak","Average","Strong"};
//武器种类
#define B 0
#define G 1
#define M 2
//攻击类型
#define BASIC 0
#define SPECIAL 1
#define SKILL 2
inline db read_db(){
	int x = read(),y = read();
	return x * powl(10,y);
}

struct Player{
	int team;//队伍
	int id;//编号
	int type;//种族
	int lv;//等级
	int hp;//体力值
	int maxhp;//体力上限
	db atk;//基础攻击指数
	db def;//基础防御指数
	int skill_lv;//主动技能等级
	int passiveskl_lv;//被动技能等级
	int weapon_type;//武器类型
	db weapon_atk;//武器攻击力
	db average_skill_effect;//average的主动技能的效果，每回合结束时对面的人要扣血
	int average_skill_effect_left;//扣血debuff还有多少个回合
	db team_atk;//队伍攻击加成
	db team_def;//队伍防御加成
	db skill_additional;//技能加成
	void input(int _team,int _id){
		team = _team;
		id = _id;
		string s;
		cin>>s;
		type = (s.size() == 4 ? WEAK : s.size() == 7 ? AVERAGE : STRONG);
		lv = read();
		maxhp = hp = read();
		atk = read_db();
		def = read_db();
		skill_lv = read();
		passiveskl_lv = read();
		cin>>s;
		weapon_type = (s[0] == 'B' ? B : s[0] == 'G' ? G : M);
		weapon_atk = read_db();
		average_skill_effect = 0;
		average_skill_effect_left = 0;
		skill_additional = 1;
	}
	inline bool is_null(){return id == 0;}//是不是null
	inline bool is_full_hp(){return hp == maxhp;}//是不是满血
	inline bool is_died(){return hp <= 0;}//是不是死了
	inline int change_hp(int x){//加血或扣血
		int oldhp = hp;
		hp = max(0,min(hp + x,maxhp));
		return hp - oldhp;
	}
	void out(){
		cerr<<"team "<<team_name[team]<<" id "<<id<<":"<<endl;
		cerr<<"type: "<<type<<" lv: "<<lv<<" hp: "<<hp<<" maxhp: "<<maxhp<<endl;
		cerr<<"atk: "<<atk<<" def: "<<def<<" skill_lv: "<<skill_lv<<" passiveskl_lv: "<<passiveskl_lv<<endl;
		cerr<<"weapon_type: "<<weapon_type<<" weapon_atk: "<<weapon_atk<<" average_skill_effect: "<<average_skill_effect<<" average_skill_effect_left: "<<average_skill_effect_left<<endl;
		cerr<<"team_atk: "<<team_atk<<" team_def: "<<team_def<<" skill_additional: "<<skill_additional<<endl<<endl;
	}
}a[2][20],null_player;
int n[2],t;
int lst[2];//每个队伍上一次行动的人
struct Attack{
	int id;//回合编号
	int type;//攻击类型
	int target;//攻击目标
	int atkpos;//攻击方位
	int ddgpos;//躲闪方位
	void input(int _id){
		id = _id;
		string s;
		cin>>s;
		target = read();
		if(s.size() == 5){
			type = SKILL;
		}
		else{
			type = (s.size() == 11 ? BASIC : SPECIAL);
			atkpos = read();
			ddgpos = read();
		}
	}
};

inline int chk_team_win(){//是否有队伍赢了
	int ans = 2;
	for(int i = 0;i < 2;++i){
		bool flag = 1;
		for(int j = 1;j <= n[i];++j) if(a[i][j].hp > 0){
			flag = 0;
			break;
		}
		if(flag){//阵营i全死了
			ans = 1 - i;
			return ans;
		}
	}
	return ans;
}

int west_to_east[] = {0,5,3,1,2,4,6};//从西到东的顺序，也是输出的编号顺序
int west_to_east_pos[] = {0,3,4,2,5,1,6};//从西到东的顺序，每个编号的人的位置
struct Output{
	void output_recovery(Player &x,int heal){//x回血heal，heal是本应增加的血量，要输出这个
		//if(!heal) return;
		if(x.is_full_hp()) return;
		x.change_hp(heal);
		cout<<team_name[x.team]<<" "<<x.id<<" recovered +"<<heal<<" hp -> "<<x.hp<<"/"<<x.maxhp<<endl;
	}
	void output_dmg(Player &x,Player &y,int dmg){//x对y造成dmg点伤害
		//if(!dmg) return;
		y.change_hp(-dmg);
		cout<<team_name[y.team]<<" "<<y.id<<" took "<<dmg<<" damage from "<<team_name[x.team]<<" "<<x.id<<" -> "<<y.hp<<"/"<<y.maxhp<<endl;
	}
	void output_dmg_skill(Player &x,int dmg){//x由于技能受到dmg点伤害
		//if(!dmg) return;
		x.change_hp(-dmg);
		cout<<team_name[x.team]<<" "<<x.id<<" took "<<dmg<<" damage from skill -> "<<x.hp<<"/"<<x.maxhp<<endl;
	}
	void output_apply_skill(Player &x,Player &y){//x对y使用技能
		cout<<team_name[x.team]<<" "<<x.id<<" applied "<<skill_name[x.type]<<" skill to "<<team_name[y.team]<<" "<<y.id<<endl;
	}
	void output_all(){
		for(int i = 1;i >= 0;--i){
			cout<<team_name[i]<<":";
			for(int j = 1;j <= 6;++j){
				int id = west_to_east[j];
				if(id > n[i]) continue;
				cout<<" "<<a[i][id].hp<<"/"<<a[i][id].maxhp;
			}
			cout<<endl;
		}
		cout<<endl;
	}
	void end_game(){//整局游戏结束
		int res = chk_team_win();
		if(res == 2) return;
		cout<<"Team "<<team_name[res]<<" won."<<endl;
	}
}output;

Player& get_west(Player &x){//获得一个人西边的第一个人，不存在返回null_player
	int team = x.team,id = west_to_east_pos[x.id];
	for(int i = id - 1;i;--i){
		if(west_to_east[i] > n[team]) continue;
		Player &y = a[team][west_to_east[i]];
		if(!y.is_died()) return y;		
	}
	return null_player;
}
Player& get_east(Player &x){//获得一个人东边的第一个人，不存在返回null_player
	int team = x.team,id = west_to_east_pos[x.id];
	for(int i = id + 1;i <= 6;++i){
		if(west_to_east[i] > n[team]) continue;
		Player &y = a[team][west_to_east[i]];
		if(!y.is_died()) return y;		
	}
	return null_player;
}


Player& get_now_player(int id){//第id个回合，获取当前行动的人
	assert(chk_team_win() == 2);
	//output.output_all();
	int team = id % 2;
	int &i = lst[team];
	//cerr<<team<<" "<<i<<":::"<<n[team]<<endl;
	i = i % n[team] + 1;
	while(a[team][i].is_died()) i = i % n[team] + 1;
	return a[team][i];
}

db weak_pskill_val[] = {0,1.3l,1.6l,1.9l,2.2l,2.5l};//weak被动技能的参数，数值是百分比
void get_weak_pskill(int team){//回合开始时，触发weak的被动技能
	for(int i = 1;i <= n[team];++i){
		Player &x = a[team][i];
		if(x.is_died()) continue;
		db val = 0;
		bool flag = 0;
		for(int j = 1;j <= n[team];++j){
			Player &y = a[team][j];
			if(y.is_died() || y.type != WEAK || y.passiveskl_lv == 0) continue;
			val += weak_pskill_val[y.passiveskl_lv];
			flag = 1;
		}
		//cerr<<team<<" "<<i<<":"<<endl;
		//x.out();
		if(flag) output.output_recovery(x,min(val,5.0l) / 100.0l * x.maxhp);
	}
}

void get_average_skill_effect(int team){//回合结束时，触发average的主动技能的掉血效果
	for(int i = 1;i <= n[team];++i){
		Player &x = a[team][i];
		if(x.is_died() || !x.average_skill_effect) continue;
		//x.out();
		output.output_dmg_skill(x,x.average_skill_effect / 100.0l * x.maxhp);
		--x.average_skill_effect_left;
		if(!x.average_skill_effect_left) x.average_skill_effect = 0;//扣血debuff到时间了
	}
}

db pskill_val[] = {0,0.01l,0.02l,0.03l,0.04l,0.05l};//其他两种被动技能的参数
void get_pskill(){//处理涉及到攻防指数的两种pskill
	for(int team = 0;team < 2;++team){
		for(int i = 1;i <= n[team];++i){
			Player &x = a[team][i];
			if(x.is_died()) continue;
			db atk_val = 0,def_val = 0;
			for(int j = 1;j <= n[team];++j){
				Player &y = a[team][j];
				if(y.is_died()) continue;
				if(y.type == AVERAGE) def_val += pskill_val[y.passiveskl_lv];//防御加成
				else if(y.type == STRONG) atk_val += pskill_val[y.passiveskl_lv];//攻击加成
			}
			x.team_atk = 1 + min(0.1l,atk_val);
			x.team_def = 1 + min(0.1l,def_val);
		}
	}

}

db fwjc[] = {1.25l,1,0.75l,0,0.75l,1};//方位加成参数
db get_fwjc(int atkpos,int ddgpos){//计算方位加成
	return fwjc[(atkpos - ddgpos + 6) % 6];
}
db zzkzjc[3][3] = {{1,0.9l,1.1l},{1.1l,1,0.9l},{0.9l,1.1l,1}};//种族克制加成参数
db get_zzkzjc(Player &plr,Player &tar){//计算种族克制加成
	return zzkzjc[plr.type][tar.type];
}
void attack(Player &plr,Player &tar,db basic_val,int atkpos,int ddgpos){//攻击结算，basic_val是基础攻击强度
	//计算「攻击强度」等于「基础攻击强度」乘以发起「攻击」的人的「技能加成」乘以队伍的「攻击加成」乘以「种族克制加成」乘以「方位加成」
	db true_val = basic_val * plr.skill_additional * plr.team_atk * get_zzkzjc(plr,tar) * get_fwjc(atkpos,ddgpos);
	output.output_dmg(plr,tar,true_val / (tar.def * tar.team_def));
	//cout<<basic_val<<" "<<true_val<<" "<<tar.def<<" "<<tar.team_def<<": "<<true_val / (tar.def * tar.team_def)<<endl;
	get_pskill();//要注意把别人干死之后更新被动技能的效果 
}

Player& get_target(Player &x,Attack atk){//获得目标成员
	//cerr<<x.team<<" "<<atk.target<<":::"<<endl;
	//a[x.team][atk.target].out();
	//a[!x.team][atk.target].out();
	if(atk.type == SKILL && x.type != AVERAGE) return a[x.team][atk.target];//己方队员
	return a[!x.team][atk.target];//对方队员
}

void basic_attack(Player &plr,Player &tar,int atkpos,int ddgpos){//发动普通攻击
	attack(plr,tar,plr.atk * plr.weapon_atk,atkpos,ddgpos);
	plr.skill_additional = 1;
}

void special_attack(Player &plr,Player &tar,int atkpos,int ddgpos){//发动特殊攻击
	if(plr.weapon_type == B){
		attack(plr,tar,plr.atk * plr.weapon_atk * 1.25l,atkpos,ddgpos);
	}
	else if(plr.weapon_type == G){
		Player &wst = get_west(tar);
		Player &est = get_east(tar);
		int cnt = 1 + !wst.is_null() + !est.is_null();
		attack(plr,tar,plr.atk * plr.weapon_atk * 1.35l / cnt,atkpos,ddgpos);
		if(!wst.is_null()) attack(plr,wst,plr.atk * plr.weapon_atk * 1.35l / cnt,atkpos,ddgpos);
		if(!est.is_null()) attack(plr,est,plr.atk * plr.weapon_atk * 1.35l / cnt,atkpos,ddgpos);
	}
	else if(plr.weapon_type == M){
		Player &wst = get_west(tar);
		Player &est = get_east(tar);
		attack(plr,tar,plr.atk * plr.weapon_atk * 1.15l,atkpos,ddgpos);
		if(!wst.is_null()) attack(plr,wst,plr.atk * plr.weapon_atk * 0.23l,atkpos,ddgpos);
		if(!est.is_null()) attack(plr,est,plr.atk * plr.weapon_atk * 0.23l,atkpos,ddgpos);
	}
	plr.skill_additional = 1;
}

db weak_skill_val[] = {0,10,12,15,17,20};//weak主动技能的参数，数值是百分比
db average_skill_val[] = {0,6,7,8,9,10};//average主动技能的参数，数值是百分比
db strong_skill_val[] = {1,2.1l,2.17l,2.24l,2.32l,2.4l};//strong主动技能的参数，注意0级的参数是1而不是0
void skill(Player &plr,Player &tar){//发动主动技能
	output.output_apply_skill(plr,tar);
	if(plr.type == WEAK){
		output.output_recovery(tar,weak_skill_val[plr.skill_lv] / 100.0l * tar.maxhp);//weak主动技能，让队友回血
	}
	else if(plr.type == AVERAGE){
		tar.average_skill_effect = average_skill_val[plr.skill_lv];//average主动技能，让对方每回合扣血
		tar.average_skill_effect_left = 3;//扣血debuff持续3个回合
		//tar.out();
	}
	else if(plr.type == STRONG){
		tar.skill_additional = strong_skill_val[plr.skill_lv];//strong主动技能，修改队友的技能加成
	}
}

void run(Attack atk){//开始一个回合
	Player &plr = get_now_player(atk.id);
	//cerr<<"now player: "<<team_name[plr.team]<<" "<<plr.id<<endl;
	get_weak_pskill(plr.team);
	//cerr<<"*****"<<endl;
	get_pskill();
	//cerr<<"*****"<<endl;
	Player &tar = get_target(plr,atk);
	//cerr<<"tar: "<<team_name[tar.team]<<" "<<tar.id<<endl;
	//tar.out();
	assert(!tar.is_died());
	if(atk.type == BASIC) basic_attack(plr,tar,atk.atkpos,atk.ddgpos);
	else if(atk.type == SPECIAL) special_attack(plr,tar,atk.atkpos,atk.ddgpos);
	else skill(plr,tar);
	get_average_skill_effect(!plr.team);
}
int main(){
	srand(time(0));rd();
	//freopen("10.in","r",stdin);
	//freopen("out.out","w",stdout);
	//file("");
	int i,j;
	n[0] = lst[0] = read();n[1] = lst[1] = read();
	for(i = 0;i < 2;++i){
		for(j = 1;j <= n[i];++j) a[i][j].input(i,j);
	}
	t = read();
	for(i = 0;i < t;++i){
		//cout<<"turn "<<i<<":"<<endl;
		Attack atk;
		atk.input(i);
		//cerr<<atk.type<<" "<<atk.target<<" "<<atk.atkpos<<" "<<atk.ddgpos<<"***"<<endl;
		run(atk);
		output.output_all();
	}
	output.end_game();
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}



