/* *
* @author GaoJun
* @file wow3.cpp
* @date 20180407
* @description wow3 开战
*  1. 战士有武器生命值、force与武器vector
*  2. 武器有攻击力、使用次数、种类等特征
*  3. 城市类有一个warrior* 可以用来存两个阵营的战士
*  4. 战士的产生、攻击、死亡等行为依靠城市的方法实现
*  5. 战士的移动以及到达城市的判定有城市完成
* */
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <deque>
using namespace std;

const int ICEMAN = 0, LION = 1, WOLF = 2, NINJA = 3, DRAGON = 4;
const int SWORD = 0, BOMB = 1, ARROW = 2;
const string COLORS[2] = { "red", "blue" };
const string WEAPONS[] = { "sword", "bomb", "arrow" };
const string WARRIORNAME[] = { "iceman", "lion", "wolf", "ninja", "dragon" };
int ORDERRED[] = { ICEMAN, LION, WOLF, NINJA, DRAGON };
int ORDERBLUE[] = { LION, DRAGON, NINJA, ICEMAN, WOLF };
const int TIME[] = { 0, 5, 10, 35, 40, 50, 55 };
int init_hp[5];
int init_force[5];
int K, M, N, T;//减少的K
int hour = 0, minute = 0;//用于计数小时和分钟的变量
class weapons
{
public:
	int _force;
	void use();
	bool used;
	int use_num;
	int _type;
	weapons(int type, int force)
	{
		switch (type)
		{
		case SWORD:
		{
			_force = force * 2/10;
			break;
		}
		case BOMB:
		{
			_force = force * 4/10;
			break;
		}
		case ARROW:
			_force = force * 3/10;
			break;
		}
		_type = type;
		used = 0;
		use_num = 0;
	}
	weapons(const weapons& _weapon)
	{
		_force = _weapon._force;
		used = _weapon._force;
		_type = _weapon._type;
		use_num = _weapon.use_num;
	}
	weapons() {};
	bool operator<(const weapons& w2)
	{
		if (_type != w2._type)
		{
			return _type < w2._type;
		}
		else if (_type == w2._type && _type == ARROW)
		{
			if (w2.used)
			{
				return true;
			}
		}
		else
		{
			return _type <= w2._type;
		}
	}
};
class warriors
{
public:
	warriors(int, int, int);
	virtual ~warriors()
	{
		int l = weaponlist.size();
		for (int i = 0; i < l; i++)
		{
			delete weaponlist[i];
		}
	}
	virtual bool will_escape() { return false; };//是否 lion会跑
	virtual void get_weapons(warriors *w) {};//用于wolf获得武器
	virtual void yelled(int time) {};//dragonyell
	virtual void downloyalty() {}; //荣誉值下降
	virtual void minus() {}; //生命值下降
	bool is_killed();//是否被杀死
	friend class city;
	int hp;
	int _color;
	int _type;
	int _id;
	int _force;
	int weapon_num;
	int arrows;
	int swords;
	int bombs;//有没有炸弹
	void tell_situation()
	{
		cout << COLORS[_color] << " " << WARRIORNAME[_type] << " " << _id << " has " << swords << " sword " << bombs
			<< " bomb " << arrows << " arrow and " << hp << " elements\n";
	}
	vector<weapons*> weaponlist;
};
warriors::warriors(int color, int id, int type)
{
	_color = color;
	_id = id;
	hp = init_hp[type];
	_force = init_force[type];
	_type = type;
	swords = 0;
	arrows = 0;
	bombs = 0;
	switch (type)
	{
	case NINJA:
	{
		weapons *p1 = new weapons(id % 3, _force);
		weapons *p2 = new weapons((id + 1) % 3, _force);
		weaponlist.push_back(p1);
		weaponlist.push_back(p2);
		break;
	}
	case ICEMAN:
	{
		weapons *p = new weapons(id % 3, _force);
		weaponlist.push_back(p);
		break;
	}
	case LION:
	{
		weapons *p = new weapons(id % 3, _force);
		weaponlist.push_back(p);
		break;
	}
	case WOLF:
	{
		break;
	}
	case DRAGON:
	{
		weapons *p = new weapons(id % 3, _force);
		weaponlist.push_back(p);
		break;
	}
	}
	weapon_num = weaponlist.size();
	for (int i = 0; i < weapon_num; i++)
	{
		switch (weaponlist[i]->_type)
		{
		case SWORD: swords++; break;
		case BOMB: bombs++; break;
		case ARROW: arrows++; break;
		}
	}
	weapon_num = swords + bombs + arrows;
	cout << setw(3) << setfill('0') << hour << ":00 " << COLORS[color] << " " << WARRIORNAME[_type] << " " << _id << " born\n";
}
bool warriors::is_killed()
{
	return hp < 0 || hp == 0;
}

class lion :public warriors
{
	int loyalty;
public:
	//
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
public:
	dragon(int color, int id, int type) :warriors(color, id, type) {};
	void yelled(int time)
	{
		cout << endl;
	}
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
public:
	iceman(int color, int id, int type) :warriors(color, id, type) {};
	void minus()
	{
		hp -= (int)hp*1 / 10;
	}
};

class  city
{
	int id;
	int color;
	int hp;
	bool isstop;
public:
	/*city (int _id, int _color, int _hp)
	{
	id = _id;
	color = _color;
	hp = _hp;

	}*/
	city()
	{
		warrior[0] = NULL;
		warrior[1] = NULL;
	}
	warriors * warrior[2];
	void init_city(int);
	void make_color(int);
	void lion_escape(int);
	bool is_taken();//是否被占领
	void create_warrior(int);
	void sort_weapons();
	void go_another_city(city*, int);//前往城市	
	void new_force();//攻击力变化
	void sort_weapon();
	void escape();
	void yell();
	void attack();
	void tell_hp();
	bool is_headsquarter();
	void makewarrior(int*, int);
	bool can_make_warrior(int key);
	bool is_stop() { return isstop; };
	void makestop() { isstop = 1; };
	void winner_get_weapons(int);
	void wolf_get_weapons(int);
} cities[21];

//初始化
void city::init_city(int id)
{
	delete warrior[0];
	delete warrior[1];
	warrior[0] = NULL;
	warrior[1] = NULL;
	isstop = 0;
	this->id = id;
}
void city::make_color(int col)
{
	this->color = col;
	this->hp = M;
}
bool cmp(weapons* w1, weapons* w2)
{
	return *w1 < *w2;
}
//创造
void city::create_warrior(int order)
{
	if (this->color)
	{
		makewarrior(ORDERBLUE, order);
	}
	else
	{
		makewarrior(ORDERRED, order);
	}
}
void city::makewarrior(int* ORDER, int order)
{
	hp -= init_hp[ORDER[order]];
	switch (ORDER[order])
	{
	case LION:
		warrior[color] = new lion(hp, color, hour + 1, ORDER[order]);
		break;
	case WOLF:
		warrior[color] = new wolf(color, hour + 1, ORDER[order]);
		break;
	case DRAGON:
		warrior[color] = new dragon(color, hour + 1, ORDER[order]);
		break;
	case ICEMAN:
		warrior[color] = new iceman(color, hour + 1, ORDER[order]);
		break;
	case NINJA:
		warrior[color] = new warriors(color, hour + 1, ORDER[order]);
		break;
	}
	//warrior[color] = new warriors(color, hour + 1, ORDER[order]);

}
bool city::can_make_warrior(int key)
{
	return hp >= init_hp[key];
}
//去另一个城市
void city::go_another_city(city* target, int _color)
{
	if (this->warrior[_color] == NULL)
	{
		return;
	}
	//iceman掉血
	if (warrior[_color]->_type == ICEMAN)
	{
		warrior[_color]->minus();
	}
	if (warrior[_color]->_type == LION)
	{
		warrior[_color]->downloyalty();
	}
	target->warrior[_color] = this->warrior[_color];
	this->warrior[_color] = NULL;
}
//生命值
void city::tell_hp()
{
	cout << setw(3) << setfill('0') << hour << ":50 " << hp << " elements in " << COLORS[color] << " headquarter\n";
}
//狮子逃跑
void city::lion_escape(int w)
{
	if (warrior[w] == NULL)return;
	if (warrior[w]->will_escape())
	{
		cout << setw(3) << setfill('0') << hour << ":05 " << COLORS[warrior[w]->_color] << " lion " << warrior[w]->_id << " ran away\n";
		delete warrior[w];
		warrior[w] = NULL;
	}
}
//武器排序
void city::sort_weapon()
{
	if (warrior[0] != NULL)
	{
		vector<weapons*> & p = warrior[0]->weaponlist;
		for (int i = 0; i < p.size(); i++)
		{
			for (int j = 0; j < p.size() - i - 1; j++)
			{
				if (*p[j + 1] < *p[j])
				{
					swap(p[j + 1], p[j]);
				}
			}
		}
	}
	if (warrior[1] != NULL)
	{
		vector<weapons*> & p = warrior[1]->weaponlist;
		for (int i = 0; i < p.size(); i++)
		{
			for (int j = 0; j < p.size() - i - 1; j++)
			{
				if (*p[j + 1] < *p[j])
				{
					swap(p[j + 1], p[j]);
				}
			}
		}
	}
}
//进攻
void city::attack()
{
	if (warrior[0] == NULL || warrior[1] == NULL)
	{
		return;
	}
	else
	{

		if (id % 2 == 1)
		{
			warriors & first = *warrior[0];
			warriors & last = *warrior[1];
			sort_weapon();
			int n1 = first.weaponlist.size();
			int n2 = last.weaponlist.size();
			for (int m = 0; m < first.weaponlist.size(); m++)
			{
				if (first.weaponlist[m]->_force == 0 && first.weaponlist[m]->_type == SWORD)
				{
					n1--;
				}
			}
			for (int m = 0; m < last.weaponlist.size(); m++)
			{
				if (last.weaponlist[m]->_force == 0 && last.weaponlist[m]->_type == SWORD)
				{
					n2--;
				}
			}
			int key1 = 0, key2 = 0;
			weapons *p1 = 0, *p2 = 0;
			while (true)
			{
				//取武器
				if (n1 != 0 )
				{
					p1 = first.weaponlist[key1];
					
					while (p1 == NULL)
					{
						key1 = (key1 + 1) % first.weaponlist.size();
						p1 = first.weaponlist[key1];
						if (first.weapon_num == 0)
						{
							first.weaponlist.clear();
							n1 = 0;
							break;
						}
					}

				}
				if (n2 != 0)
				{
					p2 = last.weaponlist[key2];
					while (p2 == NULL)
					{
						key2 = (key2 + 1) % last.weaponlist.size();
						p2 = last.weaponlist[key2];
						if (last.weapon_num == 0)
						{
							last.weaponlist.clear();
							n2 = 0;
							break;
						}
					}

				}
				int firstforce, secondforce;
				if (n1 == 0) { p1 = 0; firstforce = 0; }
				else { firstforce = p1->_force; }
				if (n2 == 0) { p2 = 0; secondforce = 0; }
				else { secondforce = p2->_force; }
				//攻击
				if (n1 != 0)
				{
					switch (p1->_type)
					{
					case SWORD:
						last.hp -= firstforce;
						break;
					case BOMB:
						last.hp -= firstforce;
						if (first._type != NINJA)
						{
							first.hp -= firstforce / 2;
						}
						n1--;
						first.bombs--;
						first.weapon_num--;
						delete first.weaponlist[key1];
						first.weaponlist[key1] = 0;
						break;
					case ARROW:
						last.hp -= firstforce;
						p1->use_num++;
						if (p1->use_num >= 2)
						{
							n1--;
							first.arrows--;
							first.weapon_num--;
							delete first.weaponlist[key1];
							first.weaponlist[key1] = 0;
						}
						break;
					}
				}
				if (first.is_killed() || last.is_killed() || (n1 == 0 && n2 == 0))
				{
					break;
				}
				if (n2 != 0)
				{
					switch (p2->_type)
					{
					case SWORD:
						first.hp -= secondforce;
						break;
					case BOMB:
						first.hp -= secondforce;
						if (last._type != NINJA)
						{
							last.hp -= secondforce / 2;
						}
						n2--;
						last.bombs--;
						last.weapon_num--;
						delete last.weaponlist[key2];
						last.weaponlist[key2] = 0;
						break;
					case ARROW:
						first.hp -= secondforce;
						p2->use_num++;
						if (p2->use_num >= 2)
						{
							n2--;
							last.arrows--;
							last.weapon_num--;
							delete last.weaponlist[key2];
							last.weaponlist[key2] = 0;
						}
						break;
					}
				}
				if (first.is_killed() || last.is_killed() || (n1 == 0 && n2 == 0))
				{
					break;
				}
				if (first.weaponlist.size())
				{
					key1 = (key1 + 1) % first.weaponlist.size();
				}
				if (last.weaponlist.size())
				{
					key2 = (key2 + 1) % last.weaponlist.size();
				}
			}
			vector<weapons*>::iterator i1 = first.weaponlist.begin();
			vector<weapons*>::iterator i2 = last.weaponlist.begin();
			vector<weapons*>temp;
			for (; i1 != first.weaponlist.end(); i1++)
			{
				if (*i1 == 0)
				{
					continue;
				}
				temp.push_back(*i1);
			}
			first.weaponlist.clear();
			first.weaponlist.assign(temp.begin(), temp.end());
			temp.clear();
			for (; i2 != last.weaponlist.end(); i2++)
			{
				if (*i2 == 0)
				{
					continue;
				}
				temp.push_back(*i2);
			}
			last.weaponlist.clear();
			last.weaponlist.assign(temp.begin(), temp.end());
			temp.clear();
			sort_weapon();
			if (first.is_killed() && last.is_killed())
			{
				cout << setw(3) << setfill('0') << hour << ":40 both red " << WARRIORNAME[first._type] << " " << first._id << " and blue " << WARRIORNAME[last._type] << " " << last._id << " died in city " << id << endl;
				delete warrior[0];
				delete warrior[1];
				warrior[0] = 0;
				warrior[1] = 0;
			}
			if ((!first.is_killed()) && (!last.is_killed()))
			{
				cout << setw(3) << setfill('0') << hour << ":40 both red " << WARRIORNAME[first._type] << " " << first._id << " and blue " << WARRIORNAME[last._type] << " " << last._id << " were alive in city " << id << endl;
			}
			if ((!first.is_killed()) && (last.is_killed()))
			{
				cout << setw(3) << setfill('0') << hour << ":40 red " << WARRIORNAME[first._type] << " " << first._id << " killed blue " << WARRIORNAME[last._type] << " " << last._id << " in city " << id << " remaining " << first.hp << " elements\n";
				winner_get_weapons(0);
				delete warrior[1];
				warrior[1] = 0;
			}
			if ((first.is_killed()) && (!last.is_killed()))
			{
				cout << setw(3) << setfill('0') << hour << ":40 blue " << WARRIORNAME[last._type] << " " << last._id << " killed red " << WARRIORNAME[first._type] << " " << first._id << " in city " << id << " remaining " << last.hp << " elements\n";
				winner_get_weapons(1);
				delete warrior[0];
				warrior[0] = 0;
			}
			yell();
		}

		if (id % 2 == 0)
		{
			warriors & first = *warrior[1];
			warriors & last = *warrior[0];
			sort_weapon();
			int n1 = first.weaponlist.size();
			int n2 = last.weaponlist.size();
			for (int m = 0; m < first.weaponlist.size(); m++)
			{
				if (first.weaponlist[m]->_force == 0 && first.weaponlist[m]->_type == SWORD)
				{
					n1--;
				}
			}
			for (int m = 0; m < last.weaponlist.size(); m++)
			{
				if (last.weaponlist[m]->_force == 0 && last.weaponlist[m]->_type == SWORD)
				{
					n2--;
				}
			}
			int key1 = 0, key2 = 0;
			weapons *p1 = 0, *p2 = 0;
			while (true)
			{
				//取武器
				if (n1 != 0)
				{
					p1 = first.weaponlist[key1];
					while (p1 == NULL)
					{
						key1 = (key1 + 1) % first.weaponlist.size();
						p1 = first.weaponlist[key1];
						if (first.weapon_num == 0)
						{
							first.weaponlist.clear();
							n1 = 0;
							break;
						}
					}

				}
				if (n2 != 0)
				{
					p2 = last.weaponlist[key2];
					while (p2 == NULL)
					{
						key2 = (key2 + 1) % last.weaponlist.size();
						p2 = last.weaponlist[key2];
						if (last.weapon_num == 0)
						{
							last.weaponlist.clear();
							n2 = 0;
							break;
						}
					}

				}
				int firstforce, secondforce;
				if (n1 == 0) { p1 = 0; firstforce = 0; }
				else { firstforce = p1->_force; }
				if (n2 == 0) { p2 = 0; secondforce = 0; }
				else { secondforce = p2->_force; }
				//攻击
				if (n1 != 0)
				{
					switch (p1->_type)
					{
					case SWORD:
						last.hp -= firstforce;
						break;
					case BOMB:
						last.hp -= firstforce;
						if (first._type != NINJA)
						{
							first.hp -= firstforce / 2;
						}
						n1--;
						first.bombs--;
						first.weapon_num--;
						delete first.weaponlist[key1];
						first.weaponlist[key1] = 0;
						break;
					case ARROW:
						last.hp -= firstforce;
						p1->use_num++;
						if (p1->use_num >= 2)
						{
							n1--;
							first.arrows--;
							first.weapon_num--;
							delete first.weaponlist[key1];
							first.weaponlist[key1] = 0;
						}
						break;
					}
				}
				if (first.is_killed() || last.is_killed() || (n1 == 0 && n2 == 0))
				{
					break;
				}
				if (n2 != 0)
				{
					switch (p2->_type)
					{
					case SWORD:
						first.hp -= secondforce;
						break;
					case BOMB:
						first.hp -= secondforce;
						if (last._type != NINJA)
						{
							last.hp -= secondforce / 2;
						}
						n2--;
						last.bombs--;
						last.weapon_num--;
						delete last.weaponlist[key2];
						last.weaponlist[key2] = 0;
						break;
					case ARROW:
						first.hp -= secondforce;
						p2->use_num++;
						if (p2->use_num >= 2)
						{
							n2--;
							last.arrows--;
							last.weapon_num--;
							delete last.weaponlist[key2];
							last.weaponlist[key2] = 0;
						}
						break;
					}
				}
				if (first.is_killed() || last.is_killed() || (n1 == 0 && n2 == 0))
				{
					break;
				}
				if (first.weaponlist.size() != 0)
				{
					key1 = (key1 + 1) % first.weaponlist.size();
				}
				if (last.weaponlist.size() != 0)
				{
					key2 = (key2 + 1) % last.weaponlist.size();
				}
			}
			vector<weapons*>::iterator i1 = first.weaponlist.begin();
			vector<weapons*>::iterator i2 = last.weaponlist.begin();
			vector<weapons*>temp;
			for (; i1 != first.weaponlist.end(); i1++)
			{
				if (*i1 == 0)
				{
					continue;
				}
				temp.push_back(*i1);
			}
			first.weaponlist.clear();
			first.weaponlist.assign(temp.begin(), temp.end());
			temp.clear();
			for (; i2 != last.weaponlist.end(); i2++)
			{
				if (*i2 == 0)
				{
					continue;
				}
				temp.push_back(*i2);
			}
			last.weaponlist.clear();
			last.weaponlist.assign(temp.begin(), temp.end());
			temp.clear();
			sort_weapon();
			if (first.is_killed() && last.is_killed())
			{
				cout << setw(3) << setfill('0') << hour << ":40 both red " << WARRIORNAME[last._type] << " " << last._id << " and blue " << WARRIORNAME[first._type] << " " << first._id << " died in city " << id << endl;
				delete warrior[0];
				delete warrior[1];
				warrior[0] = 0;
				warrior[1] = 0;
			}
			if ((!first.is_killed()) && (!last.is_killed()))
			{
				cout << setw(3) << setfill('0') << hour << ":40 both red " << WARRIORNAME[last._type] << " " << last._id << " and blue " << WARRIORNAME[first._type] << " " << first._id << " were alive in city " << id << endl;
			}
			if ((first.is_killed()) && (!last.is_killed()))
			{
				cout << setw(3) << setfill('0') << hour << ":40 red " << WARRIORNAME[last._type] << " " << last._id << " killed blue " << WARRIORNAME[first._type] << " " << first._id << " in city " << id << " remaining " << last.hp << " elements\n";
				winner_get_weapons(0);
				delete warrior[1];
				warrior[1] = 0;
			}
			if ((!first.is_killed()) && (last.is_killed()))
			{
				cout << setw(3) << setfill('0') << hour << ":40 blue " << WARRIORNAME[first._type] << " " << first._id << " killed red " << WARRIORNAME[last._type] << " " << last._id << " in city " << id << " remaining " << first.hp << " elements\n";
				winner_get_weapons(1);
				delete warrior[0];
				warrior[0] = 0;
			}
			yell();
		}
	}
}
//赢了的拿武器
void city::winner_get_weapons(int n)
{
	warriors & p1 = *warrior[n];
	warriors & p2 = *warrior[1-n];
	int nnum = p1.weaponlist.size();
	vector<weapons*> & lst1 = p1.weaponlist;
	vector<weapons*> & lst2 = p2.weaponlist;
	int s = p2.swords, b = p2.bombs, a = p2.arrows;
	if (lst1.size() >= 10)
	{
		return;
	}
	for (int i = 0; i < s; i++)
	{
		weapons * p = new weapons(*p2.weaponlist[i]);
		p1.weaponlist.push_back(p);
		p1.swords++;
		p1.weapon_num++;
		if (lst1.size() >= 10)
		{
			return;
		}
	}
	for (int i = s; i < s + b; i++)
	{
		weapons *p = new weapons(*lst2[i]);
		lst1.push_back(p);
		p1.bombs++;
		p1.weapon_num++;
		if (lst1.size() >= 10)
		{
			return;
		}
	}
	for (int i = lst2.size() - 1; i >= s + b; i--)
	{
		weapons *p = new weapons(*lst2[i]);
		lst1.push_back(p);
		p1.arrows++;
		p1.weapon_num++;
		if (lst1.size() >= 10)
		{
			return;
		}
	}
}
//狼人拿武器
void city::wolf_get_weapons(int n)
{
	warriors & p1 = *warrior[n];
	warriors & p2 = *warrior[1 - n];
	vector<weapons*> & lst1 = p1.weaponlist;
	vector<weapons*> & lst2 = p2.weaponlist;
	sort_weapon();
	int s = p2.swords, b = p2.bombs, a = p2.arrows;
	if (p1.weaponlist.size() >= 10) return;
	if (p2.weaponlist.size() == 0) return;
	if (s != 0)
	{
		for (int i = 0; i < s; i++)
		{
			weapons * p = new weapons(*p2.weaponlist[i]);
			p1.weaponlist.push_back(p);
			p1.swords++;
			p1.weapon_num++;
			p2.swords--;
			p2.weapon_num--;
			delete p2.weaponlist[i];
			p2.weaponlist[i] = NULL;
			if (lst1.size() >= 10)
			{
				cout << setw(3) << setfill('0') << hour << ":35 " << COLORS[n] << " " << WARRIORNAME[p1._type] << " " << p1._id << " took " << i + 1 << " sword from " << COLORS[1 - n] << " " << WARRIORNAME[p2._type] << " " << p2._id << " in city " << id << endl;
				return;
			}
		}
		cout << setw(3) << setfill('0') << hour << ":35 " << COLORS[n] << " " << WARRIORNAME[p1._type] << " " << p1._id << " took " << s << " sword from " << COLORS[1 - n] << " " << WARRIORNAME[p2._type] << " " << p2._id << " in city " << id << endl;
		return;
	}
	else if (b != 0)
	{
		for (int i = s; i < s+b; i++)
		{
			weapons * p = new weapons(*p2.weaponlist[i]);
			p1.weaponlist.push_back(p);
			p1.bombs++;
			p1.weapon_num++;
			p2.bombs--;
			p2.weapon_num--;
			delete p2.weaponlist[i];
			p2.weaponlist[i] = NULL;
			if (lst1.size() >= 10)
			{
				cout << setw(3) << setfill('0') << hour << ":35 " << COLORS[n] << " " << WARRIORNAME[p1._type] << " " << p1._id << " took " << i + 1 << " bomb from " << COLORS[1 - n] << " " << WARRIORNAME[p2._type] << " " << p2._id << " in city " << id << endl;
				return;
			}
		}
		cout << setw(3) << setfill('0') << hour << ":35 " << COLORS[n] << " " << WARRIORNAME[p1._type] << " " << p1._id << " took " << b << " bomb from " << COLORS[1 - n] << " " << WARRIORNAME[p2._type] << " " << p2._id << " in city " << id << endl;

		return;
	}
	else if (a != 0) 
	{
		int k = 0;
		for (int i = lst2.size()-1; i >= s + b; i--)
		{
			k++;
			weapons * p = new weapons(*p2.weaponlist[i]);
			p1.weaponlist.push_back(p);
			p1.arrows++;
			p1.weapon_num++;
			p2.arrows--;
			p2.weapon_num--;
			delete p2.weaponlist[i];
			p2.weaponlist[i] = NULL;
			if (lst1.size() >= 10)
			{
				cout << setw(3) << setfill('0') << hour << ":35 " << COLORS[n] << " " << WARRIORNAME[p1._type] << " " << p1._id << " took " << k << " arrow from " << COLORS[1 - n] << " " << WARRIORNAME[p2._type] << " " << p2._id << " in city " << id << endl;
				return;
			}
		}
		cout << setw(3) << setfill('0') << hour << ":35 " << COLORS[n] << " " << WARRIORNAME[p1._type] << " " << p1._id << " took " << a << " arrow from " << COLORS[1 - n] << " " << WARRIORNAME[p2._type] << " " << p2._id << " in city " << id << endl;

		return;
	}
	
}

//欢呼
void city::yell()
{
	if (warrior[0] != NULL)
	{
		if (warrior[0]->_type == DRAGON)
		{
			cout << setw(3) << setfill('0') << hour << ":40 red dragon " << warrior[0]->_id << " yelled in city " << id << endl;
		}
	}
	if (warrior[1] != NULL)
	{
		if (warrior[1]->_type == DRAGON)
		{
			cout << setw(3) << setfill('0') << hour << ":40 blue dragon " << warrior[1]->_id << " yelled in city " << id << endl;
		}
	}
}
//攻击力变化
void city::new_force()
{
	
	if (warrior[0] != 0)
	{
		vector<weapons*> & lst = warrior[0]->weaponlist;
		if (lst.size()!= 0)
		{
			//warrior[0]->weapon_num = lst.size();
			//warrior[0]->arrows = 0;
			//warrior[0]->bombs = 0;
			//warrior[0]->swords = 0;
			vector<weapons*>::iterator i = lst.begin();
			for (; i != lst.end(); i++)
			{
				switch ((*i)->_type)
				{
				case SWORD:
				{
					(*i)->_force = warrior[0]->_force * 2 / 10;
					//warrior[0]->swords++;
					break;
				}
				case BOMB:
				{
					(*i)->_force = warrior[0]->_force * 4 / 10;
					//warrior[0]->bombs++;
					break;
				}
				case ARROW:
					(*i)->_force = warrior[0]->_force * 3 / 10;
					//warrior[0]->arrows++;
					break;
				}
			}
		}
	}
	if (warrior[1] != 0)
	{
		vector<weapons*> & lst = warrior[1]->weaponlist;
		if (lst.size() != 0)
		{
			//warrior[1]->weapon_num = lst.size();
			//warrior[1]->arrows = 0;
			//warrior[1]->bombs = 0;
			//warrior[1]->swords = 0;
			vector<weapons*>::iterator i = lst.begin();
			
			for (; i != lst.end(); i++)
			{
				switch ((*i)->_type)
				{
				case SWORD:
				{
					(*i)->_force = warrior[1]->_force * 2 / 10;
					//warrior[1]->swords = 0;
					break;
				}
				case BOMB:
				{
					(*i)->_force = warrior[1]->_force * 4 / 10;
					//warrior[1]->bombs++;
					break;
				}
				case ARROW:
					//warrior[1]->arrows++;
					(*i)->_force = warrior[1]->_force * 3 / 10;
					break;
				}
			}
		}
	}
}
int main(int argv, char** argc)
{
	int t;
	//ofstream out("out.txt");
	//streambuf * oldbuf = cout.rdbuf(out.rdbuf());
	cin >> t;

	for (int i = 1; i <= t; i++)
	{
		cin >> M >> N >> K >> T;
		cin >> init_hp[DRAGON] >> init_hp[NINJA] >> init_hp[ICEMAN] >> init_hp[LION] >> init_hp[WOLF];
		cin >> init_force[DRAGON] >> init_force[NINJA] >> init_force[ICEMAN] >> init_force[LION] >> init_force[WOLF];
		int total_hour = T / 60;
		int total_min = T % 60;
		hour = 0;
		minute = 0;
		cout << "Case " << i << ":\n";
		for (int m = 0; m <= N + 1; m++)
		{
			cities[m].init_city(m);
		}
		cities[0].make_color(0);
		cities[N + 1].make_color(1);
		int red_o = 0;
		int blue_o = 0;
		int rflag = 0, bflag = 0;
		for (hour = 0; hour <= total_hour; hour++)
		{
			//0分制造武士
			//红
			if (!cities[0].is_stop())
			{
				int r1 = 0;
				if (cities[0].can_make_warrior(ORDERRED[red_o]))
				{
					cities[0].create_warrior(red_o);
					red_o = (red_o + 1) % 5;
				}
				else
				{
					cities[0].makestop();
				}
			}
			//蓝
			if (!cities[N + 1].is_stop())
			{
				int r1 = 0;
				if (cities[N + 1].can_make_warrior(ORDERBLUE[blue_o]))
				{
					cities[N + 1].create_warrior(blue_o);
					blue_o = (blue_o + 1) % 5;
				}
				else
				{
					cities[N + 1].makestop();
				}
			}

			//5分狮子逃跑
			minute = 5;
			if (hour == total_hour && minute > total_min) { break; }
			cities[0].lion_escape(0);
			for (int var = 1; var < N + 1; var++)
			{
				cities[var].lion_escape(0);
				cities[var].lion_escape(1);
			}
			cities[N + 1].lion_escape(1);

			//10分出发
			minute = 10;
			if (hour == total_hour && minute > total_min) { break; }
			for (int var1 = 1; var1 <= N + 1; var1++)
			{
				cities[var1].go_another_city(cities + var1 - 1, 1);
				cities[N + 1 - var1].go_another_city(cities + N + 1 - var1 + 1, 0);
			}
			for (int var = 0; var <= N + 1; var++)
			{
				if (cities[var].warrior[0] != NULL)
				{
					warriors& p = *cities[var].warrior[0];
					if (var != N + 1)
					{
						cout << setw(3) << setfill('0') << hour << ":10 " << "red " << WARRIORNAME[p._type] << " " << p._id << " marched to city " << var << " with " << p.hp << " elements and force " << p._force << endl;
					}
					else
					{
						cout << setw(3) << setfill('0') << hour << ":10 " << "red " << WARRIORNAME[p._type] << " " << p._id << " reached blue headquarter with " << p.hp << " elements and force " << p._force << endl;

						cout << setw(3) << setfill('0') << hour << ":10" << " blue headquarter was taken\n";
						rflag = 1;
					}
				}
				if (cities[var].warrior[1] != NULL)
				{
					warriors& p = *cities[var].warrior[1];
					if (var != 0)
					{
						cout << setw(3) << setfill('0') << hour << ":10 " << "blue " << WARRIORNAME[p._type] << " " << p._id << " marched to city " << var << " with " << p.hp << " elements and force " << p._force << endl;

					}
					else
					{
						cout << setw(3) << setfill('0') << hour << ":10 " << "blue " << WARRIORNAME[p._type] << " " << p._id << " reached red headquarter with " << p.hp << " elements and force " << p._force << endl;
						cout << setw(3) << setfill('0') << hour << ":10" << " red headquarter was taken\n";
						bflag = 1;
					}

				}
			}
			if (rflag || bflag)break;

			//35分钟抢武器
			minute = 35;
			if (hour == total_hour && minute > total_min) { break; }
			for (int var = 1; var <= N; var++)
			{
				if (cities[var].warrior[0] != NULL && cities[var].warrior[1] != NULL)
				{
					if (cities[var].warrior[0]->_type == WOLF && cities[var].warrior[1]->_type != WOLF)
					{
						
						cities[var].wolf_get_weapons(0);
						vector<weapons*>::iterator i1 = cities[var].warrior[1]->weaponlist.begin();
						vector<weapons*>temp;
						for (; i1 != cities[var].warrior[1]->weaponlist.end(); i1++)
						{
							if (*i1 == NULL)
							{
								continue;
							}
							temp.push_back(*i1);
						}
						cities[var].warrior[1]->weaponlist.clear();
						cities[var].warrior[1]->weaponlist.assign(temp.begin(), temp.end());
						temp.clear();

					}
					if (cities[var].warrior[1]->_type == WOLF && cities[var].warrior[0]->_type != WOLF)
					{
						cities[var].wolf_get_weapons(1);
						vector<weapons*>::iterator i1 = cities[var].warrior[0]->weaponlist.begin();
						vector<weapons*>temp;
						for (; i1 != cities[var].warrior[0]->weaponlist.end();i1++)
						{
							if (*i1 == 0)
							{
								continue;
							}
							temp.push_back(*i1);
						}
						cities[var].warrior[0]->weaponlist.clear();
						cities[var].warrior[0]->weaponlist.assign(temp.begin(), temp.end());
						temp.clear();

					}
					
				}
			}
			for (int var = 1; var <= N; var++)
			{
				cities[var].new_force();
			}

			//40分钟开始打架
			minute = 40;
			if (hour == total_hour && minute > total_min) { break; }
			for (int var = 1; var <= N; var++)
			{
				cities[var].attack();
			}

			//50分，司令部报告它拥有的生命元数量。
			minute = 50;
			if (hour == total_hour && minute > total_min) { break; }
			cities[0].tell_hp();
			cities[N + 1].tell_hp();
			//55分，每个武士报告其拥有的武器情况
			minute = 55;
			if (hour == total_hour && minute >= total_min) { break; }
			for (int var = 1; var <= N; var++)
			{
				if (cities[var].warrior[0] != NULL)
				{
					cout << setw(3) << setfill('0') << hour << ":55 ";
					cities[var].warrior[0]->tell_situation();
				}
				if (cities[var].warrior[1] != NULL)
				{
					cout << setw(3) << setfill('0') << hour << ":55 ";
					cities[var].warrior[1]->tell_situation();
				}
			}
		}
	}
	return 0;
}