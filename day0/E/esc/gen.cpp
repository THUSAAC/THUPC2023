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
}
struct dat
{
    double maxhp[4][111];
    double tonextexp[101];
    double atkpoint[4][111];
    double defpoint[4][111];
    double weaponatk[4][71];
    int weaponupdate[4][71];
    int skillupdate[6];
}data;
void init()
{
    int i,j;
    data.atkpoint[1][0]=1.003;
    data.atkpoint[1][1]=0.75;
    data.atkpoint[2][0]=1.005;
    data.atkpoint[2][1]=0.8;
    data.atkpoint[3][0]=1.005;
    data.atkpoint[3][1]=1;
    data.defpoint[1][0]=1.024;
    data.defpoint[1][1]=0.01;
    data.defpoint[2][0]=1.0225;
    data.defpoint[2][1]=0.2;
    data.defpoint[3][0]=1.02585;
    data.defpoint[3][1]=10;
    data.maxhp[1][0]=1.045;
    data.maxhp[1][1]=100000;
    data.maxhp[2][0]=1.0404;
    data.maxhp[2][1]=5000;
    data.maxhp[3][0]=1.0366;
    data.maxhp[3][1]=100;
    for(i=1;i<=3;i++)
        for(j=2;j<=110;j++)
            data.atkpoint[i][j]=data.atkpoint[i][j-1]*data.atkpoint[i][0];
    for(i=1;i<=3;i++)
        for(j=2;j<=110;j++)
            data.defpoint[i][j]=data.defpoint[i][j-1]*data.defpoint[i][0];
    for(i=1;i<=3;i++)
        for(j=2;j<=110;j++)
            data.maxhp[i][j]=data.maxhp[i][j-1]*data.maxhp[i][0];
}

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
    Real(double x){
        assert(x>=1e-2&&x<100000);
        exp=0;
        //while(x>=100000)x/=10,++exp;
        while(x+1e-9<10000)x*=10,--exp;
        mag=x+1e-9;
    }
    operator std::string() const {
        assert(mag>=1&&mag<100000);
        assert(exp>=-6&&exp<=0);
        return std::to_string(int(mag))+"e"+std::to_string(exp);
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
	target.recover(effect[level]);
}
void Askill::cast(Player& target) const {
	const Real effect[6]={0, Real(6,-2), Real(7,-2), Real(8,-2), Real(9,-2), Real(10,-2)};
	target.askilleffect=effect[level];
	target.askillturn=3;
}
void Sskill::cast(Player& target) const {
	const Real effect[6]={1, Real(210,-2), Real(217,-2), Real(224,-2), Real(232,-2), Real(240,-2)};
	target.power=effect[level];
}

Player::~Player(){
	delete weapon;
	delete skill;
}
bool Player::kd() const{
	return hp<=0;
}
int atkpos,ddgpos;
void Player::attack(Player& target) {
	Real posmul=pos[(atkpos+6-ddgpos)%6];
	Real mul=posmul*power*spassive();
	weapon->attack(target, mul);
	power=1;
}
void Player::specialattack(Player& target) {
	Real posmul=pos[(atkpos+6-ddgpos)%6];
	Real mul=posmul*power*spassive();
	weapon->specialattack(target, mul);
	power=1;
}
void Player::cast(Player& target) const{
	skill->cast(target);
}
void Player::takedamage(const Real& dmg){
	Real strength=dmg*resist[dmgsource->type][type];
	__int128 realdmg=strength/(def*apassive());
	hp-=realdmg;
	cmax(hp,0);
}
void Player::recover(const Real& percentage){
	if(hp==maxhp)return;
	int realheal=percentage*Real(maxhp);
	hp+=realheal;
	cmin(hp,maxhp);
}
void Player::takepercentagedamage(const Real& percentage){
	int realdmg=percentage*Real(maxhp);
	hp-=realdmg;
	cmax(hp,0);
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

std::mt19937 gen(std::random_device{}());
int R(int l, int r){
    return std::uniform_int_distribution<>(l,r)(gen);
}
char token[22];
int main(){
	init();
    int basiclvl=R(63,97);
	int n=R(5,6),m=R(5,6);
    printf("%d %d\n",n,m);
	team[0].cnt=n;
	team[1].cnt=m;
	for(int i=0;i<n+m;++i){
		Player& player=i<n?team[0].player[notopos[i]]:team[1].player[notopos[i-n]];
		player.no=i<n?i+1:i-n+1;
		player.team=i<n?team:team+1;
        int type=R(1,3);
        if(type==1){
            strcpy(token,"Weak");
        }
        if(type==2){
            strcpy(token,"Average");
        }
        if(type==3){
            strcpy(token,"Strong");
        }
        printf("%s ",token);
        
		int lv=basiclvl+R(-3,3);//lv
        printf("Lv=%d ",lv);

		player.hp=player.maxhp=data.maxhp[type][lv];
        printf("maxhp=%d ",player.maxhp);
		Real atk=Real(data.atkpoint[type][lv]);
        printf("atk=%s ",std::string(atk).c_str());
		player.def=Real(data.defpoint[type][lv]);
        printf("def=%s ",std::string(player.def).c_str());
        int skilllv=R(0,5);
        if(player.type!=strong)skilllv=0;
			else skilllv=5;
        printf("skillLv=%d ",skilllv);
		if(*token=='W'){
			player.type=weak;
			player.skill=new Wskill(skilllv);
		}
		else if(*token=='A'){
			player.type=average;
			player.skill=new Askill(skilllv);
		}
		else{//S
			player.type=strong;
			player.skill=new Sskill(skilllv);
		}
		int passivelevel=R(0,5);
        if(player.type==weak)passivelevel=0;
        printf("passivesklLv=%d ",passivelevel);
		player.passiveeffect=passiveeffect[player.type][passivelevel];
        token[0]="BGM"[R(0,2)];
		printf("%c ",token[0]);
        int health=player.def*Real(player.maxhp);
        double weaponatk=std::uniform_real_distribution<>(0.002*health,0.0025*health)(gen);
        cmax(weaponatk,300);
        cmin(weaponatk,80000);
        Real realwpatk(weaponatk);
		if(*token=='B'){
			player.weapon=new Bow(atk*realwpatk);
		}
		else if(*token=='G'){
			player.weapon=new Gun(atk*realwpatk);
		}
		else{//M
			player.weapon=new Mortar(atk*realwpatk);
		}
        printf("weaponatk=%s\n",std::string(realwpatk).c_str());
	}
    std::vector<std::string> op;
	int turn=0;
    int T=R(10000,50000);
	while(T--){
        int cnt=0;
        for(int i=1;i<=team[turn].cnt;++i){
            cnt+=!team[turn][i].kd();
        }
        if(cnt==0)break;
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
        int mv;
        if(curplayer.skill->level)mv=R(0,2);
            else mv=R(1,2);
        if(mv==0)strcpy(token,"Skill");
            else if(mv==1)strcpy(token,"Basicattack");
            else if(mv==2)strcpy(token,"Specialattack");
		if(token[1]=='k'){
			int targetno;
            do{
                targetno=curplayer.type==average?R(1,team[turn^1].cnt):R(1,team[turn].cnt);
            }
            while(team[curplayer.type==average?turn^1:turn][targetno].kd());
            op.push_back("Skill target="+std::to_string(targetno));
			Player& target=curplayer.type==average?team[turn^1][targetno]:team[turn][targetno];
			curplayer.cast(target);
		}
		else{
            int targetno;
            do{
                targetno=R(1,team[turn^1].cnt);
            }
            while(team[turn^1][targetno].kd());
			Player& target=team[turn^1][targetno];
            atkpos=R(1,6);
            ddgpos=R(1,6);
			if(token[1]=='a'){
                op.push_back("Basicattack target="+std::to_string(targetno)+" atkpos="+std::to_string(atkpos)+" ddgpos="+std::to_string(ddgpos));
				curplayer.attack(target);
			}
			else{//p
                op.push_back("Specialattack target="+std::to_string(targetno)+" atkpos="+std::to_string(atkpos)+" ddgpos="+std::to_string(ddgpos));
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
		turn^=1;
	}
    printf("%zu\n",op.size());
    for(auto &s:op){
        printf("%s\n",s.c_str());
    }
	return 0;
}