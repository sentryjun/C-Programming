#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <memory.h>
#include <sstream>
using namespace std;

const int WARRIORNUMS = 5;
const string warrior_name[WARRIORNUMS] = { "iceman", "lion", "wolf", "ninja", "dragon" };
int REDS[] = { 0, 1, 2, 3, 4 };//red顺序
int BLUES[] = { 1, 4, 3, 0, 2 };//blus顺序
int sths[5];//血量
class warrior;
class headsquarter {
	int total_hp;
	int num;
	string name;
	int warriors[WARRIORNUMS];
	int orders[WARRIORNUMS];
	bool stop;
public:
	friend class warrior;
	headsquarter(const string&, int, int*);
	bool Canmakewarrior(int ord, int t);
	void makeWarrior(int, int);
	bool IsStopped();
	void makestop();
	string getcolor();
};
class warrior {
	int hps;
	string types;
	string heads;
public:
	warrior(int, int, int, int, int, const string&);
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
warrior::warrior(int id, int hp, int nums, int time, int types, const string& heads) :types(warrior_name[types]), heads(heads)
{
	hps = hp;
	stringstream ss;
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
	warrior(num, sths[orders[ord]], warriors[orders[ord]], t, orders[ord], name);
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
void game(int cases, int M, int* hps);

int main(int argv, char** argcs)
{
	//int REDS[] = {0, 1, 2, 3, 4};
	//int BLUES[] = {1, 4, 3, 0, 2};

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