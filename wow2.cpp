/**
 * @author GaoJun
 * @Date 20180320
 * @description: C++Prpgramming Homework wow
 * 
 */
#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <memory.h>
#include <fstream>
#include <sstream>
using namespace std;

void game(int cases, int M, int* hps);
const int WARRIORNUMS = 5;
const string warrior_name[WARRIORNUMS] = { "iceman", "lion", "wolf", "ninja", "dragon" };
int REDS[] = { 0, 1, 2, 3, 4 };//red顺序
int BLUES[] = { 1, 4, 3, 0, 2 };//blus顺序
int sths[5];//血量
const string WEAPONS[] = {"sword", "bomb", "arrow"};
class warrior;
class weapon;
class headsquarter {
	int total_hp;
	int num;
	string name;
	int warriors[WARRIORNUMS];
	int orders[WARRIORNUMS];
	bool stop;
public:
	friend class warrior;
	friend class dragon; 
	friend class ninja;
	friend class lion;
	friend class iceman;
	friend class weapon;
	headsquarter(const string&, int, int*);
	bool Canmakewarrior(int ord, int t);
	void makeWarrior(int, int);
	bool IsStopped();
	void makestop();
	string getcolor();
};
//战士类
class warrior {
	public:
	int hps;
	string types;
	string heads;
	headsquarter *headptr;
	warrior(int, int, int, int, int, const string&, headsquarter *p = NULL);
};
//武器类
class weapon {
public:
	string name;
	double typicalvalue;
	weapon(int name, double value = 0):name(WEAPONS[name])
	{
		typicalvalue = value;
	}
};

//iceman类
class iceman:warrior
{
public:
	weapon sword;
	iceman(int, int, int, int, int, const string&, headsquarter *p);
};

//lion类
class lion:warrior
{
public:
	int loyalty;
	lion(int, int, int, int, int, const string&, headsquarter *p);
};
//ninja
class ninja:warrior
{
	public:
	weapon ninjaweapons1;
	weapon ninjaweapons2;
	ninja(int, int, int, int, int, const string&, headsquarter *p);
};
//dragon
class dragon:warrior
{
	public:
	weapon dragonweapon;
	double morale;
	dragon(int, int, int, int, int, const string&, headsquarter *p);
};

headsquarter::headsquarter(const string& pname, int hp, int* order) :name(pname)
{
	total_hp = hp;
	memcpy(orders, order, sizeof(orders));
	for (int i = 0; i < 5; i++)
	{
		orders[i] = order[i];
	}
	num = 0;
	stop = 0;
	memset(warriors, 0, sizeof(warriors));
	//cout << orders[0] << orders[1];
}
warrior::warrior(int id, int hp, int nums, int time, int types, const string& heads, headsquarter *p) :types(warrior_name[types]), heads(heads)
{
	hps = hp;
	stringstream ss;
	headptr = p;
	ss << setw(3) << setfill('0') << time;
	ss << " " + this->heads + " " + this->types + " " << id << " born with strength " << hp << "," << nums << " " + this->types + " in " + this->heads << " headquarter\n";
	cout << ss.str();
}
bool headsquarter::Canmakewarrior(int ord, int t)
{
	if (sths[orders[ord]] > total_hp)
	{
		return false;
	}
	return true;
}
void headsquarter::makeWarrior(int ord, int t)
{
	total_hp -= sths[orders[ord]];
	warriors[orders[ord]]++;
	num++;
	switch(orders[ord])
	{
		case 0:iceman(num, sths[orders[ord]], warriors[orders[ord]], t, orders[ord], name, this);break;
		case 1:lion(num, sths[orders[ord]], warriors[orders[ord]], t, orders[ord], name, this);break;
		case 2:warrior(num, sths[orders[ord]], warriors[orders[ord]], t, orders[ord], name, this);break;
		case 3:ninja(num, sths[orders[ord]], warriors[orders[ord]], t, orders[ord], name, this);break;
		case 4:dragon(num, sths[orders[ord]], warriors[orders[ord]], t, orders[ord], name, this);break;
	}
	//warrior(num, sths[orders[ord]], warriors[orders[ord]], t, orders[ord], name);
}
bool headsquarter::IsStopped()
{
	return stop;
}
string headsquarter::getcolor()
{
	return string(name);
}
void headsquarter::makestop()
{
	stop = 1;
}


iceman::iceman(int id, int hp, int nums, int time, int types, const string& heads, headsquarter *p):warrior(id, hp, nums, time, types, heads, p),sword(id%3)
{
	cout << "It has a " + WEAPONS[id%3] << endl;;
}

lion::lion(int id, int hp, int nums, int time, int types, const string& heads, headsquarter*p):warrior(id, hp, nums, time, types, heads, p)
{
	loyalty = p->total_hp;
	cout << "It's loyalty is " << loyalty << endl;
}
ninja::ninja(int id, int hp, int nums, int time, int types, const string& heads, headsquarter*p):warrior(id, hp, nums, time, types, heads, p),ninjaweapons1(id%3), ninjaweapons2((id+1)%3)
{
	cout << "It has a " << WEAPONS[id%3]<<" and a " << WEAPONS[(id+1)%3] << endl;
}
dragon::dragon(int id, int hp, int nums, int time, int types, const string& heads, headsquarter *p):warrior(id, hp, nums, time, types, heads, p),dragonweapon(id%3, ((double)(p->total_hp))/hp)
{
	morale = (double)(p->total_hp)*hp;
	cout << "It has a "+ WEAPONS[id%3]<<",and it's morale is ";
	cout << setiosflags(ios::fixed)  << setprecision(2) << (double)(p->total_hp)/hp << endl;
}


int main(int argv, char** argcs)
{
	//int REDS[] = {0, 1, 2, 3, 4};
	//int BLUES[] = {1, 4, 3, 0, 2};
	ofstream out("out.txt");
	streambuf * oldbuf = cout.rdbuf(out.rdbuf());

	int n, M;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> M;
		cin >> sths[4] >> sths[3] >> sths[0] >> sths[1] >> sths[2];
		game(i, M, sths);
	}
	return 0;
}

void game(int cases, int M, int *sths)
{
	cout << "Case:" << cases << endl;
	headsquarter red("red", M, REDS), blue("blue", M, BLUES);
	int i1 = 0, i2 = 0;
	for (int i = 0; (!red.IsStopped()) || (!blue.IsStopped()); i++)
	{
		int t1 = 0, t2 = 0;
		if (!red.IsStopped())
		{
			if (red.Canmakewarrior(i1, i))
			{
				red.makeWarrior(i1, i);
				i1 = (i1 + 1) % 5;
			}

			else
			{
				t1++;
				while (t1 != 5)
				{
					i1 = (i1 + 1) % 5;
					if (red.Canmakewarrior(i1, i))
					{
						red.makeWarrior(i1, i);
						i1 = (i1 + 1) % 5;
						break;
					}
					t1++;
					if (t1 == 5)
					{
						red.makestop();
						cout << setw(3) << setfill('0') << i;
						cout << " " << red.getcolor() << " headquarter stops making warriors\n";
					}
				}
			}
		}


		if (!blue.IsStopped())
		{
			if (blue.Canmakewarrior(i2, i))
			{
				blue.makeWarrior(i2, i);
				i2 = (i2 + 1) % 5;
			}
			else
			{
				t2++;
				while (t2 != 5)
				{
					i2 = (i2 + 1) % 5;
					if (blue.Canmakewarrior(i2, i))
					{
						blue.makeWarrior(i2, i);
						i2 = (i2 + 1) % 5;
						break;
					}
					t2++;
					if (t2 == 5)
					{
						blue.makestop();
						cout << setw(3) << setfill('0') << i;
						cout << " " << blue.getcolor() << " headquarter stops making warriors\n";
					}
				}
			}
		}
	}
	// system("pause");
}