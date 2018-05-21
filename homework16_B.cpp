#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;
vector<string>stringArray;
int s;
string ROOT = "ROOT";
template<class T>
struct cmp
{
	bool operator()(T *s1, T* s2)
	{
		return *s1 < *s2;
	}
};
void print(string & str, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "|     ";
	}
	cout << str << endl;
}

void func(int depth, string & str)
{
	set<string*, cmp<string> >sset;
	print(str, depth);
	while (true && s < stringArray.size())
	{
		string temp = stringArray[s];
		if (stringArray[s][0] == 'f')
		{
			sset.insert(&(stringArray[s]));
			s++;
		}
		else if (stringArray[s][0] == 'd')
		{
			s++;
			func(depth + 1, temp);
		}

		else
		{
			s++;
			break;
		}
	}
	set<string*, cmp<string> >::iterator it = sset.begin();
	for (; it != sset.end(); it++)
	{
		print(**it, depth);
	}
	return;
}
int main(int argv, char**argcs)
{
	int numCase = 0;
	while (true)
	{
		numCase++;
		string a;
		while (true)
		{
			cin >> a;
			if (a == "*" || a == "#")
			{
				break;
			}
			stringArray.push_back(a);
		}
		s = 0;
		if (a == "#")
		{
			break;
		}
		cout << "DATA SET " << numCase << ":\n";
		func(0, ROOT);

		stringArray.clear();
		cout << endl;
	}
	return 0;
}