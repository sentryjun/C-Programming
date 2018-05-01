/**
* @file wowfinal.cpp
* @author GaoJun
* @description 程设魔兽终极版
*
*
*
*
*
* */
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int ICEMAN = 0, LION = 1, WOLF = 2, NINJA = 3, DRAGON = 4;
const int SWORD = 0, BOMB = 1, ARROW = 2;
const int RED = 0, BLUE = 1;
const string COLORS[2] = { "red", "blue" };
const string WEAPONS[] = { "sword", "bomb", "arrow" };
const string WARRIOR[] = { "iceman", "lion", "wolf", "ninja", "dragon" };
vector<int>RV;
vector<int>BV;
int ORDERRED[] = { ICEMAN, LION, WOLF, NINJA, DRAGON };
int ORDERBLUE[] = { LION, DRAGON, NINJA, ICEMAN, WOLF };
int init_hp[5], init_force[5];
int N, M, K, T, R;
int hour, minute;
int total_hour, total_min, RID, BID;
class weapons
{
public:
	int _type;
	int _force;
	int use_num;
	weapons(int type, int force) : _type(type), _force(force * 2 / 10), use_num(0) {}
	weapons(weapons &weapon)
	{
		_type = weapon._type;
		_force = weapon._force;
		use_num = weapon.use_num;
	}
	void unsharpen()
	{
		if (this == NULL)return;
		if (_type == SWORD)
			_force = _force * 8 / 10;
	};
};
class warriors
{
public:
	int _id, _type, _force, _color, _hp, _arrows, _swords, _bombs, _weapon_nums;
	vector<weapons *> wlist;
	weapons* arrow;
	weapons* bomb;
	weapons* sword;
	warriors(int id, int type, int color);
	virtual ~warriors() {};
	virtual bool will_escape() { return false; };
	virtual void downloyality() {
		return;
	}
	virtual bool yell() { return false; };
	virtual void iceman_change() {};
	virtual void change_morale(int op) {};
	virtual void step_plus() {};
	virtual void get_weapons(warriors * defeated) { return; };
	void tell_situation();
	bool is_dead() { return _hp <= 0; };
	void clear() {
		vector<weapons*>::iterator it = wlist.begin();
		for (; it != wlist.end();) {
			if (*it == NULL) { wlist.erase(it); }
			else it++;
		}
	}
	void sword20() {
		if (sword != NULL && sword->_force == 0) {
			delete sword;
			sword = NULL;
			_swords--;
			_weapon_nums--;
			clear();
		}
	}

};
warriors::warriors(int color, int id, int type) : _id(id), _type(type), _color(color)
{
	_hp = init_hp[type];
	_force = init_force[type];
	_swords = 0;
	_arrows = 0;
	_bombs = 0;
	sword = 0;
	bomb = 0;
	arrow = 0;
	switch (type)
	{
	case NINJA:
	{
		weapons *p1 = new weapons(id % 3, _force);
		weapons *p2 = new weapons((id + 1) % 3, _force);
		wlist.push_back(p1);
		wlist.push_back(p2);
		break;
	}
	case ICEMAN:
	{
		weapons *p = new weapons(id % 3, _force);
		wlist.push_back(p);
		break;
	}
	case LION:
	{
		//weapons *p = new weapons(id % 3, _force);
		//wlist.push_back(p);
		break;
	}
	case WOLF:
	{
		break;
	}
	case DRAGON:
	{
		weapons *p = new weapons(id % 3, _force);
		wlist.push_back(p);
		break;
	}
	}
	_weapon_nums = wlist.size();
	vector<weapons *>::iterator it = wlist.begin();
	for (; it != wlist.end(); it++)
	{
		switch ((*it)->_type)
		{
		case SWORD:
			_swords++;
			sword = *it;
			break;
		case BOMB:
			_bombs++;
			bomb = *it;
			break;
		case ARROW:
			_arrows++;
			arrow = *it;
			break;
		}
	}
	sword20();
	cout << setw(3) << setfill('0') << hour << ":00 " << COLORS[_color] << " " << WARRIOR[_type] << " " << id << " born" << endl;
}
class lion : public warriors
{
	int loyalty;

public:
	lion(int _l, int color, int id, int type) : warriors(color, id, type)
	{
		loyalty = _l;
		cout << "Its loyalty is " << _l << endl;
	}
	virtual void downloyality()
	{
		loyalty -= K;
	}
	bool will_escape()
	{
		if (loyalty <= 0)
		{
			return true;
		}
		return false;
	}
};
class dragon : public warriors
{
	double morale;

public:
	dragon(int m, int color, int id, int type) : warriors(color, id, type)
	{
		morale = (double)m / (init_hp[type]);
		cout << "Its morale is " << setiosflags(ios::fixed) << setprecision(2) << morale << endl;
	}
	void yelled(int time)
	{
		cout << endl;
	}
	virtual void change_morale(int op)
	{
		if (op)
			morale += 0.2;
		else
		{
			morale -= 0.2;
		}
	}
	bool yell() { return (!is_dead()) && (morale > 0.8); };
};

class wolf : public warriors
{
public:
	wolf(int color, int id, int type) : warriors(color, id, type) {};
	void get_weapons(warriors *w)
	{
		if (sword == NULL) {
			sword = w->sword;
			w->sword = NULL;
		}
		if (arrow == NULL) {
			arrow = w->arrow;
			w->arrow = NULL;
		}
		if (bomb == NULL) {
			bomb = w->bomb;
			w->bomb = NULL;
		}
	}
};

class iceman : public warriors
{
	int step;

public:
	iceman(int color, int id, int type) : warriors(color, id, type), step(0) {};
	void iceman_change()
	{
		if (step < 2)
			return;
		if (_hp - 9 <= 0)
		{
			_hp = 1;
			_force += 20;
		}
		else if (_hp - 9 > 0)
		{
			_hp -= 9;
			_force += 20;
		}
		step = 0;
	}
	void step_plus() { step++; };
};

class city
{
public:
	int _id, _color, hp, _flag;
	int made_hp, enemy_num, red_win, blue_win;
	warriors *enemy;
	warriors *warrior[2];
	void attack();
	void init(int);
	void make_headqarter();
	void battle();
	void use_arrow(int color);
	void use_bomb();
	void bomb(int color);
	void use_sword();
	void flag_up();
	void tell_hp();
	void tell_situation(int color);
	void go_another_city(city *, int);
	void create_warrior(int);
	void lion_escape(int);
	void dragon_up();
	void get_weapons(int);
	void make_warrior(int *, int);
	void yell();
	void award_hp();
	bool can_make_warrior(int);
	void make_hp();
	void get_hp(int color);
	void clear() {
		if (warrior[0] != NULL && warrior[0]->is_dead()) {
			delete warrior[0];
			warrior[0] = NULL;
		}
		if (warrior[1] != NULL && warrior[1]->is_dead()) {
			delete warrior[1];
			warrior[1] = NULL;
		}
	}
} cities[22];
void city::init(int id)
{
	_id = id;
	_flag = -1;
	red_win = 0;
	blue_win = 0;
	made_hp = 0;
	warrior[0] = NULL;
	enemy = NULL;
	warrior[1] = NULL;
	if (id == 0)
	{
		_color = RED;
		hp = M;
		enemy_num = 0;
	}
	if (id == N + 1)
	{
		_color = BLUE;
		hp = M;
		enemy_num = 0;
	}
}
void city::create_warrior(int order)
{
	if (this->_color)
	{
		make_warrior(ORDERBLUE, order);
	}
	else
	{
		make_warrior(ORDERRED, order);
	}
}
void city::make_warrior(int *ORDER, int order)
{
	hp -= init_hp[ORDER[order]];
	int id = (this->_color == RED) ? RID : BID;
	switch (ORDER[order])
	{
	case LION:
		warrior[_color] = new lion(hp, _color, id, ORDER[order]);
		break;
	case WOLF:
		warrior[_color] = new wolf(_color, id, ORDER[order]);
		break;
	case DRAGON:
		warrior[_color] = new dragon(hp, _color, id, ORDER[order]);
		break;
	case ICEMAN:
		warrior[_color] = new iceman(_color, id, ORDER[order]);
		break;
	case NINJA:
		warrior[_color] = new warriors(_color, id, ORDER[order]);
		break;
	}
}
bool city::can_make_warrior(int key)
{
	return hp >= init_hp[key];
}
void city::make_hp() { made_hp += 10; }
void city::go_another_city(city *target, int color)
{
	if (this->warrior[color] == NULL)
		return;
	if (warrior[color]->_type == ICEMAN)
	{
		warrior[color]->step_plus();
		warrior[color]->iceman_change();
	}
	target->warrior[color] = warrior[color];
	warrior[color] = NULL;
}
void city::lion_escape(int w)
{
	if (warrior[w] == NULL)
		return;
	if (warrior[w]->will_escape())
	{
		cout << setw(3) << setfill('0') << hour << ":05 " << COLORS[warrior[w]->_color] << " lion " << warrior[w]->_id << " ran away\n";
		delete warrior[w];
		warrior[w] = NULL;
	}
}
void city::get_hp(int color) {
	int temp = made_hp;
	if (color == RED) {
		cities[0].hp += temp;
	}
	if (color == BLUE) {
		cities[N+1].hp += temp;
	}
	made_hp = 0;
}
void city::use_arrow(int color) {
	if (warrior[color] == NULL || warrior[color]->arrow == 0) {
		return;
	}
	int nextid = (color == RED) ? _id + 1 : _id - 1;
	int _enemycolor = 1 - color;
	if (nextid == 0 || nextid == N + 1 || cities[nextid].warrior[_enemycolor] == NULL) {
		return;
	}
	warriors & user = *warrior[color];
	warriors & enemy = *(cities[nextid].warrior[_enemycolor]);
	int force = R;
	enemy._hp -= force;
	user.arrow->use_num++;
	if (user.arrow->use_num >= 3) {
		delete user.arrow;
		user.arrow = NULL;
		user._arrows--;
		user._weapon_nums--;
		user.clear();
	}
	cout << setw(3) << setfill('0') << hour << ":35 " << COLORS[color] << " " << WARRIOR[user._type] << " " << user._id << " shot";
	if (enemy.is_dead()) {
		cout << " and killed " << COLORS[enemy._color] << " " << WARRIOR[enemy._type] << " " << enemy._id;
	}
	cout << endl;
}
void city::use_bomb() {
	warriors * first;
	warriors * last;
	if (_flag < 0) {
		first = (_id % 2 == 1) ? warrior[0] : warrior[1];
		last = (_id % 2 == 1) ? warrior[1] : warrior[0];
	}
	else {
		first = warrior[_flag];
		last = warrior[1 - _flag];
	}
	if (first == NULL || last == NULL || first->is_dead() || last->is_dead()) {
		return;
	}
	int first_force = 0;
	int second_force = 0;
	if (first->sword != NULL) {
		first_force = first->sword->_force;
	}
	if (last->_hp <= first_force + first->_force) {
		if (last->bomb != NULL)bomb(last->_color);
		return;
	}
	if (last->sword != NULL) {
		second_force = last->sword->_force;
	}
	if (last->_type != NINJA && first->bomb != NULL && first->_hp <= second_force + (last->_force) / 2) {
		bomb(first->_color);
		return;
	}
}
void city::bomb(int color) {
	cout << setw(3) << setfill('0') << hour << ":38 " << COLORS[color] << " " << WARRIOR[warrior[color]->_type] << " " << warrior[color]->_id << " used a bomb and killed " << COLORS[1 - color] << " " << WARRIOR[warrior[1 - color]->_type] << " " << warrior[1 - color]->_id << endl;
	delete warrior[color];
	delete warrior[1 - color];
	warrior[0] = NULL;
	warrior[1] = NULL;
}
void city::tell_hp()
{
	cout << setw(3) << setfill('0') << hour << ":50 " << hp << " elements in " << COLORS[_color] << " headquarter\n";
}
void city::tell_situation(int color) {
	if (warrior[color] == NULL) {
		return;
	}

	warriors & w = *warrior[color];
	cout << setw(3) << setfill('0') << hour << ":55 " << COLORS[w._color] << " " << WARRIOR[w._type] << " " << w._id << " has ";
	bool flag = true;
	if (w.arrow != NULL) {
		cout << "arrow" << "(" << 3 - w.arrow->use_num << ")";
		flag = false;
	}
	if (w.bomb != NULL) {
		if (flag == false) {
			cout << ",";
		}
		cout << "bomb";
		flag = false;
	}
	if (w.sword != NULL) {
		if (flag == false) {
			cout << ",";
		}
		cout << "sword(" << w.sword->_force << ")";
		flag = false;
	}
	if (flag) { cout << "no weapon"; }
	cout << endl;
}
void city::battle() {
	if (warrior[0] == NULL || warrior[1] == NULL) {
		return;
	}
	int first = RED;
	int rflag = 0, bflag = 0, flag = -1;
	if (_flag == BLUE || (_flag < 0 && _id % 2 == 0)) {
		first = BLUE;
	}
	if (warrior[0]->is_dead()) {
		bflag = 1;
	}
	if (warrior[1]->is_dead()) {
		rflag = 1;
	}
	warriors & fw = *warrior[first];
	warriors & lw = *warrior[1 - first];
	int fhp = fw._hp;
	int lhp = lw._hp;
	if (rflag == 0 && bflag == 0) {
		int attack = 0;
		if (fw.sword != NULL) {
			attack = fw.sword->_force;
		}
		lw._hp -= attack + fw._force;
		cout << setw(3) << setfill('0') << hour << ":40 " << COLORS[first] << " " << WARRIOR[fw._type] << " " << fw._id << " attacked " << COLORS[1 - first] << " " << WARRIOR[lw._type] << " " << lw._id << " in city " << _id << " with " << fw._hp << " elements and force " << fw._force << endl;
		fw.sword->unsharpen();
		if (!lw.is_dead() && lw._type != NINJA) {
			attack = 0;
			if (lw.sword != NULL) {
				attack = lw.sword->_force;
			}
			fw._hp -= attack + (lw._force / 2);
			lw.sword->unsharpen();
			cout << setw(3) << setfill('0') << hour << ":40 " << COLORS[1 - first] << " " << WARRIOR[lw._type] << " " << lw._id << " fought back against " << COLORS[first] << " " << WARRIOR[fw._type] << " " << fw._id << " in city " << _id << endl;
			if (fw.is_dead()) {
				if (fw._type == LION) lw._hp += fhp;
				cout << setw(3) << setfill('0') << hour << ":40 " << COLORS[first] << " " << WARRIOR[fw._type] << " " << fw._id << " was killed in city " << _id << endl;
			}
		}
		if (lw.is_dead()) {
			if (lw._type == LION) fw._hp += lhp;
			cout << setw(3) << setfill('0') << hour << ":40 " << COLORS[1 - first] << " " << WARRIOR[lw._type] << " " << lw._id << " was killed in city " << _id << endl;
		}
	}
	if (warrior[0]->is_dead()) {
		bflag = 1;
	}
	if (warrior[1]->is_dead()) {
		rflag = 1;
	}
	if (rflag == 0 && bflag == 0) {
		warrior[0]->downloyality();
		warrior[0]->change_morale(0);
		warrior[1]->downloyality();
		warrior[1]->change_morale(1);
		red_win = 0;
		blue_win = 0;
	}
	if (rflag == 0 && bflag == 1) {
		warrior[1]->change_morale(1);
		red_win = 0;
		blue_win++;
		flag = 1;
		
	}
	if (rflag == 1 && bflag == 0) {
		warrior[0]->change_morale(1);
		blue_win = 0;
		red_win++;
		flag = 0;
		
	}
	if (fw.yell()) {
		cout << setw(3) << setfill('0') << hour << ":40 " << COLORS[first] << " " << WARRIOR[fw._type] << " " << fw._id << " yelled in city " << _id << endl;
	}
	fw.sword20();
	lw.sword20();
	if (flag >= 0) {
		if (flag == RED) RV.push_back(_id);
		if (flag == BLUE) BV.push_back(_id);
		cout << setw(3) << setfill('0') << hour << ":40 " << COLORS[flag] << " " << WARRIOR[warrior[flag]->_type] << " " << warrior[flag]->_id << " earned " << made_hp << " elements for his headquarter" << endl;
	}
	if (red_win >= 2 && _flag != RED) {
		_flag = RED;
		cout << setw(3) << setfill('0') << hour << ":40 red flag raised in city " << _id << endl;
	}
	if (blue_win >= 2 && _flag != BLUE) {
		_flag = BLUE;
		cout << setw(3) << setfill('0') << hour << ":40 blue flag raised in city " << _id << endl;
	}
	if (flag >= 0) warrior[flag]->get_weapons(warrior[1 - flag]);
}
int main(int argv, char **argc)
{
	int t;
	//ofstream out("out.txt");
	//streambuf *oldbuf = cout.rdbuf(out.rdbuf());
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		cin >> M >> N >> R >> K >> T;
		cin >> init_hp[DRAGON] >> init_hp[NINJA] >> init_hp[ICEMAN] >> init_hp[LION] >> init_hp[WOLF];
		cin >> init_force[DRAGON] >> init_force[NINJA] >> init_force[ICEMAN] >> init_force[LION] >> init_force[WOLF];
		int total_hour = T / 60;
		int total_min = T % 60;
		hour = 0;
		minute = 0;
		for (int var = 0; var <= N + 1; var++)
		{
			cities[var].init(var);
		}
		cout << "Case " << i << ":\n";
		int red_o = 0, blue_o = 0, rflag = 0, bflag = 0;
		RID = 0; BID = 0;
		for (hour = 0; hour <= total_hour; hour++)
		{
			RV.clear();
			BV.clear();
			//0分制造武士
			if (cities[0].can_make_warrior(ORDERRED[red_o]))
			{
				RID++;
				cities[0].create_warrior(red_o);
				red_o = (red_o + 1) % 5;
			}
			if (cities[N + 1].can_make_warrior(ORDERBLUE[blue_o]))
			{
				BID++;
				cities[N + 1].create_warrior(blue_o);
				blue_o = (blue_o + 1) % 5;
			}
			//5分狮子逃跑
			minute = 5;
			if (hour == total_hour && minute > total_min)
				break;
			cities[0].lion_escape(0);
			for (int var = 1; var < N + 1; var++)
			{
				cities[var].lion_escape(0);
				cities[var].lion_escape(1);
			}
			cities[N + 1].lion_escape(1);
			//10分出发
			minute = 10;
			if (hour == total_hour && minute > total_min)
				break;
			for (int var1 = 1; var1 <= N + 1; var1++)
			{
				cities[var1].go_another_city(cities + var1 - 1, 1);
				cities[N + 1 - var1].go_another_city(cities + N + 1 - var1 + 1, 0);
			}
			for (int var = 0; var <= N + 1; var++)
			{
				if (cities[var].warrior[RED] != NULL)
				{
					warriors &p = *cities[var].warrior[RED];

					if (var != N + 1)
					{
						cout << setw(3) << setfill('0') << hour << ":10 "
							<< "red " << WARRIOR[p._type] << " " << p._id << " marched to city " << var << " with " << p._hp << " elements and force " << p._force << endl;
					}
					else
					{
						cout << setw(3) << setfill('0') << hour << ":10 "
							<< "red " << WARRIOR[p._type] << " " << p._id << " reached blue headquarter with " << p._hp << " elements and force " << p._force << endl;
						if (cities[N + 1].enemy_num == 0)
						{
							cities[N + 1].enemy_num++;
							cities[N + 1].enemy = cities[N + 1].warrior[RED];
							cities[N + 1].warrior[RED] = 0;
						}
						if (cities[N + 1].enemy!= NULL && cities[N+1].warrior[0] != NULL)
						{
							cout << setw(3) << setfill('0') << hour << ":10"
								<< " blue headquarter was taken\n";
							rflag = 1;
						}
					}
				}
				if (cities[var].warrior[BLUE] != NULL)
				{
					warriors &p = *cities[var].warrior[BLUE];

					if (var != 0)
					{
						cout << setw(3) << setfill('0') << hour << ":10 "
							<< "blue " << WARRIOR[p._type] << " " << p._id << " marched to city " << var << " with " << p._hp << " elements and force " << p._force << endl;
					}
					else
					{
						cout << setw(3) << setfill('0') << hour << ":10 "
							<< "blue " << WARRIOR[p._type] << " " << p._id << " reached red headquarter with " << p._hp << " elements and force " << p._force << endl;
						if (cities[0].enemy_num == 0)
						{
							cities[0].enemy_num++;
							cities[0].enemy = cities[0].warrior[BLUE];
							cities[0].warrior[BLUE] = 0;
						}
						else if (cities[0].enemy_num >= 1)
						{
								cout << setw(3) << setfill('0') << hour << ":10"
									<< " red headquarter was taken\n";
								rflag = 1;
						}
						
					}
				}
			}
			if (rflag || bflag)break;
			//20分生产生命元
			minute = 20;
			if (hour == total_hour && minute > total_min)
				break;
			for (int var = 1; var <= N; var++)
			{
				cities[var].make_hp();
			};
			//30分取得生命元
			minute = 30;
			if (hour == total_hour && minute > total_min)
				break;
			for (int var = 1; var <= N; var++) {
				warriors * p1 = cities[var].warrior[RED];
				warriors * p2 = cities[var].warrior[BLUE];
				if (p1 == NULL && p2 != NULL) { 
					cout << setw(3) << setfill('0') << hour << ":30 " << COLORS[p2->_color] << " " << WARRIOR[p2->_type] << " " << p2->_id << " earned " << cities[var].made_hp << " elements for his headquarter" << endl;
					cities[var].get_hp(BLUE); 
				}
				if (p1 != NULL && p2 == NULL) { 
					cout << setw(3) << setfill('0') << hour << ":30 " << COLORS[p1->_color] << " " << WARRIOR[p1->_type] << " " << p1->_id << " earned " << cities[var].made_hp << " elements for his headquarter" << endl;
					cities[var].get_hp(RED);
				}
			}
			//35分放箭
			minute = 35;
			if (hour == total_hour && minute > total_min)
				break;
			for (int var = 1; var <= N; var++) {
				cities[var].use_arrow(RED);
				cities[var].use_arrow(BLUE);
			}
			//38分炸弹
			minute = 38;
			if (hour == total_hour && minute > total_min)
				break;
			for (int var = 1; var <= N; var++) {
				cities[var].use_bomb();
			}
			//40分战斗
			minute = 40;
			if (hour == total_hour && minute > total_min)
				break;
			for (int var = 1; var <= N; var++) {
				cities[var].battle();
			}
			for (int i = RV.size() - 1; i >= 0; i--) {
				if (cities[0].hp >= 8) {
					cities[0].hp -= 8;
					cities[RV[i]].warrior[0]->_hp += 8;
				}
			}
			for (int i = 0; i < BV.size(); i++) {
				if (cities[N + 1].hp >= 8) {
					cities[N + 1].hp -= 8;
					cities[BV[i]].warrior[1]->_hp += 8;
				}
			}
			for (int i = RV.size() - 1; i >= 0; i--) cities[RV[i]].get_hp(RED);
			for (int i = BV.size() - 1; i >= 0; i--)cities[BV[i]].get_hp(BLUE);
			for (int var = 1; var <= N; var++) {
				cities[var].clear();
			}
			//50分司令部报告
			minute = 50;
			if (hour == total_hour && minute > total_min)
				break;
			cities[0].tell_hp();
			cities[N + 1].tell_hp();
			//55分武士报告
			minute = 55;
			if (hour == total_hour && minute > total_min)
				break;
			
			for (int var = 1; var <= N; var++) {
				cities[var].tell_situation(RED);
			}
			if (cities[N+1].enemy != NULL) {
				warriors & w = *cities[N+1].enemy;
				cout << setw(3) << setfill('0') << hour << ":55 " << COLORS[w._color] << " " << WARRIOR[w._type] << " " << w._id << " has ";
				bool flag = true;
				if (w.arrow != NULL) {
					cout << "arrow" << "(" << 3 - w.arrow->use_num << ")";
					flag = false;
				}
				if (w.bomb != NULL) {
					if (flag == false) {
						cout << ",";
					}
					cout << "bomb";
					flag = false;
				}
				if (w.sword != NULL) {
					if (flag == false) {
						cout << ",";
					}
					cout << "sword(" << w.sword->_force << ")";
					flag = false;
				}
				if (flag) { cout << "no weapon"; }
				cout << endl;
			}

			if (cities[0].enemy != NULL) {
				warriors & w = *cities[0].enemy;
				cout << setw(3) << setfill('0') << hour << ":55 " << COLORS[w._color] << " " << WARRIOR[w._type] << " " << w._id << " has ";
				bool flag = true;
				if (w.arrow != NULL) {
					cout << "arrow" << "(" << 3 - w.arrow->use_num << ")";
					flag = false;
				}
				if (w.bomb != NULL) {
					if (flag == false) {
						cout << ",";
					}
					cout << "bomb";
					flag = false;
				}
				if (w.sword != NULL) {
					if (flag == false) {
						cout << ",";
					}
					cout << "sword(" << w.sword->_force << ")";
					flag = false;
				}
				if (flag) { cout << "no weapon"; }
				cout << endl;
			}
			for (int var = 1; var <= N; var++) {
				cities[var].tell_situation(BLUE);
			}
		}
	}
	return 0;
}