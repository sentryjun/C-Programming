#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if (s) {
			p = new char[strlen(s) + 1];
			strcpy(p, s);
		}
		else
			p = NULL;

	}
	~MyString() { if (p) delete[] p; }
	void Copy(const char* init_char)
	{
		p = new char[strlen(init_char) + 1];
		strcpy(p, init_char);
	}
	MyString(const MyString& init) {
		p = new char[strlen(init.p) + 1];
		strcpy(p, init.p);
	}
	MyString& operator=(const char* init_c)
	{
		Copy(init_c);
		return *this;
	}
	friend ostream& operator<< (ostream& out, const MyString& data);
};

ostream& operator<< (ostream& out, const MyString& data)
{
	cout << data.p;
	return out;
};

int main()
{
	char w1[200], w2[100];
	while (cin >> w1 >> w2) {
		MyString s1(w1), s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;

	}
}
