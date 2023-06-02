#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io{
	int F(){
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G(){
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
char token[22];

enum Playertype{
	weak, average, strong
};

struct Real{
	__int128 mag;
	int exp;
	Real(int x):mag(x),exp(0){}
	Real():Real(1){}
	Real(__int128 _mag, int _exp):mag(_mag),exp(_exp){}
	Real(int (*read)()){
		mag=read();
		exp=read();
	}
	operator int() const {
		__int128 ret=mag;
		for(int i=-1;i>=exp;--i){
			ret/=10;
		}
		return ret;
	}
	Real operator *(const Real &rhs) const {
		return Real(mag*rhs.mag, exp+rhs.exp);
	}
	int operator /(const Real &rhs) const {
		__int128 n=mag,d=rhs.mag;
		for(int i=exp;i>rhs.exp;--i){
			n*=10;
		}
		for(int i=rhs.exp;i>exp;--i){
			d*=10;
		}
		return n/d;
	}
	Real operator +(const Real &rhs) const {
		assert(exp==rhs.exp);
		return Real(mag+rhs.mag, exp);
	}
};
const Real resist[3][3]={
	{1, Real(9,-1), Real(11,-1)},
	{Real(11,-1), 1, Real(9,-1)},
	{Real(9,-1), Real(11,-1), 1}
};
const Real pos[6]={Real(125,-2), 1, Real(75,-2), 0, Real(75,-2), 1};
struct Player;
Player* dmgsource;

struct Weapon{
	Real atk;
	Weapon(const Real& _atk):atk(_atk){}
	void attack(Player& target, const Real& multiplier) const;
	virtual void specialattack(Player& target, const Real& multiplier) const =0;
};
struct Bow:Weapon{
	Bow(const Real& _atk):Weapon(_atk){}
	virtual void specialattack(Player& target, const Real& multiplier) const;
};
struct Gun:Weapon{
	Gun(const Real& _atk):Weapon(_atk){}
	virtual void specialattack(Player& target, const Real& multiplier) const;
};
struct Mortar:Weapon{
	Mortar(const Real& _atk):Weapon(_atk){}
	virtual void specialattack(Player& target, const Real& multiplier) const;
};

const Real passiveeffect[3][6]={
	{Real(0,-3), Real(13,-3), Real(16,-3), Real(19,-3), Real(22,-3), Real(25,-3)},
	{Real(0,-2), Real(1,-2), Real(2,-2), Real(3,-2), Real(4,-2), Real(5,-2)},
	{Real(0,-2), Real(1,-2), Real(2,-2), Real(3,-2), Real(4,-2), Real(5,-2)}
};

struct Skill{
	int level;
	Skill(int _level):level(_level){}
	virtual void cast(Player& target) const =0;
};
struct Wskill:Skill{
	Wskill(int _level):Skill(_level){}
	virtual void cast(Player& target) const;
};
struct Askill:Skill{
	Askill(int _level):Skill(_level){}
	virtual void cast(Player& target) const;
};
struct Sskill:Skill{
	Sskill(int _level):Skill(_level){}
	virtual void cast(Player& target) const;
};

struct Team;

struct Player{
	int no;
	Playertype type;
	int hp;
	int maxhp;
	Real def;
	Weapon* weapon;
	Skill* skill;
	Team* team;
	Real passiveeffect;
	Real power;
	int askillturn;
	Real askilleffect;
	Player():askilleffect(0){}
	~Player();
	bool kd() const;
	void attack(Player& target);
	void specialattack(Player& target);
	void cast(Player& target) const;
	void takedamage(const Real& dmg);
	void recover(const Real& percentage);
	void takepercentagedamage(const Real& percentage);
	Real wpassive() const;
	Real apassive() const;
	Real spassive() const;
	Player* findwest();
	Player* findeast();
};

const int notopos[6]={2,3,1,4,0,5};

struct Team{
	int cnt;
	int cur;
	std::string name;
	Player player[6];
	Team(const std::string& _name):name(_name),cur(0){}
	Player& operator [](int no){
		return player[notopos[no-1]];
	}
	void print() const;
}team[2]={Team("South"), Team("North")};

int main(){
	int n=io::F(),m=io::F();
	team[0].cnt=n;
	team[1].cnt=m;
	for(int i=0;i<n+m;++i){
		Player& player=i<n?team[0].player[notopos[i]]:team[1].player[notopos[i-n]];
		player.no=i<n?i+1:i-n+1;
		player.team=i<n?team:team+1;
		scanf("%s",token);
		io::F();//lv
		player.hp=player.maxhp=io::F();
		Real atk(io::F);
		player.def=Real(io::F);
		if(*token=='W'){
			player.type=weak;
			player.skill=new Wskill(io::F());
		}
		else if(*token=='A'){
			player.type=average;
			player.skill=new Askill(io::F());
		}
		else{//S
			player.type=strong;
			player.skill=new Sskill(io::F());
		}
		int passivelevel=io::F();
		player.passiveeffect=passiveeffect[player.type][passivelevel];
		scanf("%s",token);
		if(*token=='B'){
			player.weapon=new Bow(atk*Real(io::F));
		}
		else if(*token=='G'){
			player.weapon=new Gun(atk*Real(io::F));
		}
		else{//M
			player.weapon=new Mortar(atk*Real(io::F));
		}
	}
	int T=io::F();
	int turn=0;
	while(T--){
		Real percentage=team[turn][1].wpassive();
		if(percentage.mag>0){
			for(int i=1;i<=team[turn].cnt;++i){
				if(!team[turn][i].kd()){
					team[turn][i].recover(percentage);
				}
			}
		}
		do{
			team[turn].cur++;
			if(team[turn].cur>team[turn].cnt){
				team[turn].cur=1;
			}
		}
		while(team[turn][team[turn].cur].kd());
		Player& curplayer=team[turn][team[turn].cur];
		dmgsource=&curplayer;
		scanf("%s",token);
		if(token[1]=='k'){
			int targetno=io::F();
			Player& target=curplayer.type==average?team[turn^1][targetno]:team[turn][targetno];
			curplayer.cast(target);
		}
		else{
			Player& target=team[turn^1][io::F()];
			if(token[1]=='a'){
				curplayer.attack(target);
			}
			else{//p
				curplayer.specialattack(target);
			}
			curplayer.power=1;
		}
		for(int i=1;i<=team[turn^1].cnt;++i){
			Player& player=team[turn^1][i];
			if(!player.kd()&&player.askillturn>0){
				player.takepercentagedamage(player.askilleffect);
				--player.askillturn;
			}
		}
		team[1].print();
		team[0].print();
		puts("");
		turn^=1;
	}
	int cnt=0;
	for(int i=1;i<=team[turn].cnt;++i){
		cnt+=!team[turn][i].kd();
	}
	if(cnt==0){
		printf("Team %s won.\n",turn?"South":"North");
	}
	return 0;
}

void Weapon::attack(Player& target, const Real& multiplier) const {
	target.takedamage(multiplier*atk);
}
void Bow::specialattack(Player& target, const Real& multiplier) const {
	target.takedamage(multiplier*atk*Real(125,-2));
}
void Gun::specialattack(Player& target, const Real& multiplier) const {
	int cnt=1;
	auto west=target.findwest();
	auto east=target.findeast();
	if(west)++cnt;
	if(east)++cnt;
	const Real effect[4]={1, Real(135,-2), Real(675,-3), Real(45,-2)};
	target.takedamage(multiplier*atk*effect[cnt]);
	if(west){
		west->takedamage(multiplier*atk*effect[cnt]);
	}
	if(east){
		east->takedamage(multiplier*atk*effect[cnt]);
	}
}
void Mortar::specialattack(Player& target, const Real& multiplier) const {
	auto west=target.findwest();
	auto east=target.findeast();
	target.takedamage(multiplier*atk*Real(115,-2));
	if(west){
		west->takedamage(multiplier*atk*Real(23,-2));
	}
	if(east){
		east->takedamage(multiplier*atk*Real(23,-2));
	}
}

void Wskill::cast(Player& target) const {
	const Real effect[6]={0, Real(10,-2), Real(12,-2), Real(15,-2), Real(17,-2), Real(20,-2)};
	printf("Weak skill to %s %d\n", target.team->name.c_str(), target.no);
	target.recover(effect[level]);
}
void Askill::cast(Player& target) const {
	const Real effect[6]={0, Real(6,-2), Real(7,-2), Real(8,-2), Real(9,-2), Real(10,-2)};
	printf("Average skill to %s %d\n", target.team->name.c_str(), target.no);
	target.askilleffect=effect[level];
	target.askillturn=3;
}
void Sskill::cast(Player& target) const {
	const Real effect[6]={1, Real(210,-2), Real(217,-2), Real(224,-2), Real(232,-2), Real(240,-2)};
	printf("Strong skill to %s %d\n", target.team->name.c_str(), target.no);
	target.power=effect[level];
}

Player::~Player(){
	delete weapon;
	delete skill;
}
bool Player::kd() const{
	return hp<=0;
}
void Player::attack(Player& target) {
	int atkpos=io::F(),ddgpos=io::F();
	Real posmul=pos[(atkpos+6-ddgpos)%6];
	Real mul=posmul*power*spassive();
	weapon->attack(target, mul);
	power=1;
}
void Player::specialattack(Player& target) {
	int atkpos=io::F(),ddgpos=io::F();
	Real posmul=pos[(atkpos+6-ddgpos)%6];
	Real mul=posmul*power*spassive();
	weapon->specialattack(target, mul);
	power=1;
}
void Player::cast(Player& target) const{
	printf("%s %d applied ", team->name.c_str(), no);
	skill->cast(target);
}
void Player::takedamage(const Real& dmg){
	Real strength=dmg*resist[dmgsource->type][type];
	long long realdmg=strength/(def*apassive());
	hp-=realdmg;
	cmax(hp,0);
	printf("%s %d took %lld damage from %s %d -> %d/%d\n", team->name.c_str(), no, realdmg, dmgsource->team->name.c_str(), dmgsource->no, hp, maxhp);
}
void Player::recover(const Real& percentage){
	if(hp==maxhp)return;
	int realheal=percentage*Real(maxhp);
	hp+=realheal;
	cmin(hp,maxhp);
	printf("%s %d recovered +%d hp -> %d/%d\n", team->name.c_str(), no, realheal, hp, maxhp);
}
void Player::takepercentagedamage(const Real& percentage){
	int realdmg=percentage*Real(maxhp);
	hp-=realdmg;
	cmax(hp,0);
	printf("%s %d took %d damage from skill -> %d/%d\n", team->name.c_str(), no, realdmg, hp, maxhp);
}
Real Player::wpassive() const{
	Real res(0,-3);
	for(int i=0;i<6;++i){
		if(!team->player[i].kd()&&team->player[i].type==weak){
			res=res+team->player[i].passiveeffect;
		}
	}
	cmin(res.mag,50);
	return res;
}
Real Player::apassive() const{
	Real res(100,-2);
	for(int i=0;i<6;++i){
		if(!team->player[i].kd()&&team->player[i].type==average){
			res=res+team->player[i].passiveeffect;
		}
	}
	cmin(res.mag,110);
	return res;
}
Real Player::spassive() const{
	Real res(100,-2);
	for(int i=0;i<6;++i){
		if(!team->player[i].kd()&&team->player[i].type==strong){
			res=res+team->player[i].passiveeffect;
		}
	}
	cmin(res.mag,110);
	return res;
}
Player* Player::findwest(){
	Player* now=this;
	while(now->no!=5){
		--now;
		if(!now->kd()){
			return now;
		}
		if(now->no==0){
			return nullptr;
		}
	}
	return nullptr;
}
Player* Player::findeast(){
	Player* now=this;
	while(now->no!=6){
		++now;
		if(!now->kd()){
			return now;
		}
		if(now->no==0){
			return nullptr;
		}
	}
	return nullptr;
}

void Team::print() const{
	printf("%s:",name.c_str());
	for(int i=0;i<6;++i){
		if(player[i].no){
			printf(" %d/%d", player[i].hp, player[i].maxhp);
		}
	}
	puts("");
}