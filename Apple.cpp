#include <iostream>
using namespace std;
class Apple {
// 在此处补充你的代码
public:
static int nTotalNumber;
Apple(){
    nTotalNumber++;
    PrintTotal();
}
~Apple(){
    nTotalNumber--;
    PrintTotal();
}
static void PrintTotal() {
		cout << nTotalNumber << endl; 
	}

};
int Apple::nTotalNumber = 0;
Apple Fun(const Apple & a) {
	//a.PrintTotal();
	return a;
}
int main(int argv, char** argc)
{
	Apple * p = new Apple[4];
	Fun(p[2]);
	Apple p1,p2;
	//Apple::PrintTotal ();
	delete [] p;
	//Apple::PrintTotal ();
	return 0;
}