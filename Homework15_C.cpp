#include <iostream>
#include <set>
#include <memory.h>
#include <string>
using namespace std;

const int MAX = 32;
int target[MAX];
int now[MAX];
int temp[MAX];
string tar;
string no;

bool isOK(int size, int* now)
{
	for (int i = 1; i <= size; i++)
	{
		if (target[i] != now[i])
		{
			return false;
		}
	}
	return true;
}
void enumerate(int size);
int main(int argc, char ** argv)
{

	cin >> no;
	cin >> tar;
	int size = no.length();
	for (int i = 1; i <= size; i++)
	{
		target[i] = tar[i-1] - '0';
		now[i] = no[i-1] - '0';
		temp[i] = now[i];
	}
	if (isOK(size, now))
	{
		cout << 0 << endl;
		return 0;
	}
	enumerate(size);
	return 0;
}
void enumerate(int size)
{
	int min_num = 0xfffff;
	int step = 0;
	int i = 2;
	while (i <= size)
	{
		if (now[i - 1] != target[i - 1])
		{
			step++;
			now[i - 1] = 1 - now[i - 1];
			now[i] = 1 - now[i];
			now[i + 1] = 1 - now[i + 1];
		}
		i++;
	}
	if (isOK(size, now) && step < min_num)
		min_num = step;
	step = 1;
	temp[1] = 1 - temp[1];
	temp[2] = 1 - temp[2];
	i = 2;
	while (i <= size)
	{
		if (temp[i - 1] != target[i - 1])
		{
			step++;
			temp[i - 1] = 1 - temp[i - 1];
			temp[i] = 1 - temp[i];
			temp[i + 1] = 1 - temp[i + 1];
		}
		i++;
	}
	if (isOK(size, temp) && step < min_num)
		min_num = step;
	if (min_num >= 0xfffff)
	{
		cout << "impossible\n";
	}
	else
	{
		cout << min_num << endl;
	}
}