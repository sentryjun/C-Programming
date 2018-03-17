/**
* The homework of C++ programming: world of warcraft:
* @author GaoJun
* @Date 2018/03/15
* @file wow1.cpp
* */
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <memory.h>

using namespace std;

string types[5] = { "iceman", "lion", "wolf", "ninja", "dragon" };
string hsq[2] = { "red", "blue" };
int sths[5] = { 4, 3, 0, 1, 2 };
int order[][5] = { { 0,1,2,3,4 },{ 1,4,3,0,2 } };
class headsquarter
{
public:
	int M;
	headsquarter(int M = 0);
	bool faq(int orderx)
	{
		return (M >= sths[orderx]) ? 1 : 0;
	}
};

class warrior
{
private:

	int id;
	int strength;
	string name;
	string headsquarter;

public:
	static int nums[2][5];
	static void init()
	{
		memset(nums, 0, sizeof(nums));
	}
	warrior(int t, int id, int strength, int name, int headsquarter);
};

int warrior::nums[2][5] = { 0 };
headsquarter::headsquarter(int M)
{
	this->M = M;
}
warrior::warrior(int t, int id, int strength, int name, int headsquarter)
{
	this->id = id;
	this->strength = strength;
	this->name = types[name];
	this->headsquarter = hsq[headsquarter];
	(this->nums[headsquarter][name])++;
	cout << setw(3) << setfill('0') << t;
	cout << " "+(this->headsquarter) <<" " + this->name + " " << id << " " << "born with strength " << strength
		<< "," << this->nums[headsquarter][name] << " " << this->name << " in " + this->headsquarter + " headquarter" << endl;
}

int main(int argv, char** argc)
{
	warrior::init();
	int cases;
	cin >> cases;
	for (int i = 1; i <= cases; i++)
	{
        warrior::init();
		int M;
		cin >> M;
		headsquarter bases[2] = { M, M };
		cin >> sths[4] >> sths[3] >> sths[0] >> sths[1] >> sths[2];
		cout << "Case:" << i << endl;
		int i1 = 0, i2 = 0;
		bool temp1 = 1, temp2 = 1;
		for (int t = 0; temp1 || temp2; t++)
		{
            int k1 = 0, k2 = 0;
			if (temp1)
			{
				
				if (bases[0].faq(order[0][i1]))
				{
					bases[0].M -= sths[order[0][i1]];
					warrior temp(t, t + 1, sths[order[0][i1]], order[0][i1], 0);
					i1 = (i1 + 1) % 5;
				}
				else
				{
					k1++;
					while (k1 != 5)
					{
						i1 = (i1 + 1) % 5;
						if (bases[0].faq(order[0][i1]))
						{
							bases[0].M -= sths[order[0][i1]];
							warrior temp(t, t + 1, sths[order[0][i1]], order[0][i1], 0);
							i1 = (i1 + 1) % 5;
							break;
						}
						k1++;
						if (k1 == 5)
						{
							temp1 = 0;
							cout << setw(3) << setfill('0') << t;
							cout << " " << hsq[0] << " headquarter stops making warriors\n";
						}
					}
			    }
			}

			if (temp2){
				if (bases[1].faq(order[1][i2]))
				{
					bases[1].M -= sths[order[1][i2]];
					warrior temp(t, t + 1, sths[order[1][i2]], order[1][i2], 1);
					i2 = (i2 + 1) % 5;
				}
				else
				{
					k2++;
					while (k2 != 5)
					{
						i2 = (i2 + 1) % 5;
						if (bases[1].faq(order[1][i2]))
						{
							bases[1].M -= sths[order[1][i2]];
							warrior temp(t, t + 1, sths[order[1][i2]], order[1][i2], 1);
							i2 = (i2 + 1) % 5;
							break;
						}
						k2++;
						if (k2 == 5)
						{
							temp2 = 0;
							cout << setw(3) << setfill('0') << t;
							cout << " " << hsq[1] << " headquarter stops making warriors\n";
						}
				    }
				}
			}
		}
	}
}