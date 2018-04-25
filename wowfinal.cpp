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
int ORDERRED[] = { ICEMAN, LION, WOLF, NINJA, DRAGON };
int ORDERBLUE[] = { LION, DRAGON, NINJA, ICEMAN, WOLF };
int init_hp[5], init_force[5];
int N, M, K, T, R;
int hour, minute;
int total_hour, total_min;
class weapons{
public:
    int _type;
    int _force;
    int use_num;
    weapons(int type, int force):_type(type),_force(force), use_num(0){}
    weapons(weapons & weapon){
        _type = weapon._type; _force = weapon._force; use_num = weapon.use_num;
    }
    void unsharpen(){
        if (_type == SWORD) _force = _force * 2 / 10;
    };    
};
class warriors{
public:
    int _id, _type, _force, _color, _hp, _arrows, _swords, _bombs, _weapon_nums;
    vector<weapons*>wlist;
    warriors(int id, int type,  int color);
    virtual ~warriors(){};
    virtual bool will_escape(){return false;};
    virtual void downloyality(){};
    virtual bool yell(){return false;};
    virtual void iceman_change(){};
    virtual void change_morale(int op){};
    bool is_dead(){return _hp <= 0;};
};
warriors::warriors(int id, int type, int color):_id(id),_type(type),_color(color)
{
    _hp = init_hp[type];
    _force = init_force[type];
    _swords = 0;
    _arrows = 0;
    _bombs = 0;
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
		weapons *p = new weapons(id % 3, _force);
		wlist.push_back(p);
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
    vector<weapons*>::iterator it = wlist.begin();
    for(; it != wlist.end(); it++)
    {
        switch ((*it)->_type)
		{
		case SWORD: _swords++; break;
		case BOMB: _bombs++; break;
		case ARROW: _arrows++; break;
		}
    }
}
class lion :public warriors
{
	int loyalty;
public:
	lion(int _l, int color, int id, int type) :warriors(color, id, type)
	{
		loyalty = _l;
		cout << "Its loyalty is " << _l << endl;
	}
	void downloyalty()
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
class dragon :public warriors
{
    double morale;
public:
	dragon(int m,int color, int id, int type) :warriors(color, id, type) 
    {
        morale = (double)m/(init_hp[type]);
    }
	void yelled(int time)
	{
		cout << endl;
	}
    virtual void change_morale(int op)
    {
        if(op) morale += 0.2;
        else{morale -= 0.2;}
    }
    bool yell(){return (!is_dead())&&(morale>0.8);};
};

class wolf :public warriors
{
public:
	wolf(int color, int id, int type) :warriors(color, id, type) {};
	void get_weapons(warriors* w)
	{
		if (w->_type == WOLF)
		{
			return;
		}
		else
		{
			return;
		}
	}
};

class iceman :public warriors
{
    int step;
public:
	iceman(int color, int id, int type) :warriors(color, id, type), step(0) {};
    void iceman_change(){
        if (step < 2) return;
        if (_hp - 9 <= 0){_hp = 1; _force += 20;}
        else if (_hp - 9 > 0){_hp -= 9; _force += 20;}
    }
};

class city{
public:
    int _id, _color, hp, _flag;
    int made_hp, enemy_num, red_win, blue_win;
    warriors * enemy;
    warriors * warrior[2];
    void attack();
    void init();
    void make_headqarter();
    void battle();
    void use_arrow();
    void use_bomb();
    void use_sword();
    void flag_up();
    void tell_situation();
    void go_another_city(city*, int);
    void create_warrior(int);
    void lion_escape();
    void dragon_up();
    void get_weapons(int);
    void make_warrior(int*, int);
    void yell();
    void award_hp();
}cities[21];
int main(int argv, char** argc){
    int t;
    ofstream out("out.txt");
    streambuf *oldbuf = cout.rdbuf(out.rdbuf());
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
		cout << "Case " << i << ":\n";
        

        for (hour = 0; hour <= total_hour; hour++)
        {
            //0分制造武士
            //10分出发
            //20分生产生命元
            //30分取得生命元
            //35分放箭
            //38分炸弹
            //40分战斗
            //50分司令部报告
            //55分武士报告
            
        }
    }
    return 0;
}
