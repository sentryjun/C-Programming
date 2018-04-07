#include <iostream>
#include <iomanip> 
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
// 在此处补充你的代码
public:
	class CArray
	{
	private:
		int row;
		int col;
		int size;
		T * ptr;
	public:
		CArray(int _row, int _col):row(_row), col(_col)
		{
			size = _row * _col;
			ptr = new T[size];
		}
		CArray(){ptr = NULL;}
		void init(int _row, int _col)
		{
			row = _row;
			col = _col;
			size = _row * _col;
			ptr = new T[size];
		}
		T * operator[](int i)
		{
			return this->ptr + i * col;
		}
		operator T*()
		{
			return ptr;
		}
	};
	CArray * a;
	int size;
	CArray3D (int len, int _row, int _col):size(len)
	{
		a = new CArray[len];
		for (int i = 0; i < len; i++){
			a[i].init(_row, _col);
		}
	}
	CArray& operator[](int n)
	{
		return *(a+n);
	}
};

CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);
void PrintA()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 4; ++j) {
			for(int k = 0; k < 5; ++k) 
				cout << a[i][j][k] << "," ;
			cout << endl;
		}
	}
}
void PrintB()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 2; ++j) {
			for(int k = 0; k < 2; ++k) 
				cout << b[i][j][k] << "," ;
			cout << endl;
		}
	}
}

int main()
{

	int No = 0;
	for( int i = 0; i < 3; ++ i ) {
		a[i];
		for( int j = 0; j < 4; ++j ) {
			a[j][i];
			for( int k = 0; k < 5; ++k )
				a[i][j][k] = No ++;
			a[j][i][i];	
		}
	}
	PrintA();
	memset(a[1],-1 ,20*sizeof(int));	
	memset(a[1],-1 ,20*sizeof(int));
	PrintA(); 
	memset(a[1][1],0 ,5*sizeof(int));	
	PrintA();

	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 2; ++j )
			for( int k = 0; k < 2; ++k )
				b[i][j][k] = 10.0/(i+j+k+1);
	PrintB();
	int n = a[0][1][2];
	double f = b[0][1][1];
	cout << "****" << endl;
	cout << n << "," << f << endl;
		
	return 0;
}