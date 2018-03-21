#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) 
{	int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s)
{
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;
		
}
int strcmp(const char * s1,const char * s2)
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
// 在此处补充你的代码
    char* ptr;
public:
    MyString(const char* s)
    {
        if (s) {
            ptr = new char[strlen(s)+1];
            strcpy(ptr, s);
            ptr[strlen(s)] = '\0';
        }
        else
        {
            ptr = NULL;
        }
    }
    MyString(char* s)
    {
        if (s) {
            ptr = new char[strlen(s)+1];
            strcpy(ptr, s);
            ptr[strlen(s)] = '\0';
        }
        else
        {
            ptr = NULL;
        }
    }
    MyString (const MyString& str)
    {
        if (str.ptr == NULL)
        {
            ptr = NULL;
        }
        else
        {
            ptr = new char[strlen(str.ptr)+1];
            strcpy(ptr, str.ptr);
            ptr[strlen(str.ptr)] = '\0';
        }
    }
    MyString()
    {
        ptr = NULL;
    }
    ~MyString()
    {
        delete[]ptr;
    }
    MyString& operator=(const MyString & str)
    {
        if (ptr)
        {
            delete [] ptr;
            ptr = NULL;
        }
        if (str.ptr == NULL)
        {
            ptr = NULL;
        }
        else
        {
            ptr = new char[strlen(str.ptr)+1];
            strcpy(ptr, str.ptr);
        }
        return *this;
    }
    friend ostream& operator<<(ostream &out, MyString & s)
    {
        if (s.ptr == NULL) return out;
        int l = strlen(s.ptr);
        for (int i = 0; i < l; i++){
        out << s.ptr[i];
        }
        return out;
    }
    bool operator==(const char* s)
    {
        return (strcmp(ptr, s) == 0);
    }
    bool operator==(MyString &s)
    {
        return (strcmp(ptr, s.ptr) == 0);
    }
    bool operator>(MyString& s)
    {
        return (strcmp(ptr, s.ptr) > 0);
    }
    bool operator<(MyString& s)
    {
        return (strcmp(ptr, s.ptr) < 0);
    }
    MyString operator+(const char* s)
    {
        char *p = new char[strlen(s) + strlen(ptr) + 1];
        strcpy(p, ptr);
        strcat(p, s);
        p[strlen(s) + strlen(ptr)] = '\0';
        MyString a(p);
        delete[]p;
        return a;
    }
    MyString  operator+(const MyString& s)
    {

        char *p = new char[strlen(s.ptr) + strlen(ptr) + 1];
        strcpy(p, ptr);
        strcat(p, s.ptr);
        p[strlen(s.ptr) + strlen(ptr)] = '\0';
        MyString a(p);
        delete[]p;
        return a;
    }
    MyString& operator+=(const MyString& s)
    {
        *this = *(this) + s;
        return *this;
    }
    char& operator[](int n)
    {
        return ptr[n];
    }
    friend MyString operator+(const char*s, MyString& str)
    {
        return MyString(s) + str;
    }
    char* operator()(int s, int e)
    {
        int delta = e;
        char* p = new char[e+1];
        for(int i = 0; i < delta; i++)
        {
            p[i] = ptr[s+i];
        }
        p[delta] = '\0';
        return p;
    }
};


int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	    return -1;
	else if( *s1 == *s2)
	    return 0;
	else if( *s1 > *s2 )
	    return 1;
    return 0;
}

int main(int argv, char**argc)
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}