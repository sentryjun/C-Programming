#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
	double r, i;
public:
	void Print() {
		cout << r << "+" << i << "i" << endl;
	}
	Complex(char* str)
	{
		char re[10] = { '\0' * 10 }, re1[10] = { '\0' * 10 };
		int val = 0;
		while (str[val] != '+')
		{
			re[val] = str[val];
			val++;
		}
		re[val] = '\0';
		r = atof(re);
		val++;
		int val1 = val;
		
		while (str[val] != '\0')
		{
			re1[val - val1] = str[val];
			val++;
		}
		re1[val - val1] = '\0';
		i = atof(re1);
	}
	Complex()
	{
		r = 0;
		i = 0;
	}
	// 在此处补充你的代码
};
int main() {
	Complex a;
	a = "3+4i"; a.Print();
	a = "5+6i"; a.Print();
	return 0;
}