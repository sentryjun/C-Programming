#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110;
class CHugeInt {
	// 在此处补充你的代码
	int len;
	char MaxNums[220];
public:
	CHugeInt(char* str)
	{
		len = strlen(str);
		strcpy(MaxNums, str);
		int i = 0, j = len - 1;
		while (i < j)
		{
			swap(MaxNums[i], MaxNums[j]);
			i++;
			j--;
		}
	}
	CHugeInt()
	{
		len = 0;
	}
	CHugeInt(int n)
	{
		int i = 0;
		if (n == 0)
		{
			MaxNums[i++] = '0';
		}
		else
		{
			while (n)
			{
				MaxNums[i] = (n % 10) + '0';
				n /= 10;
				i++;
			}
		}
		int t = 0, j = i - 1;
		MaxNums[i] = '\0';
		len = i;
	}

	friend ostream& operator<<(ostream& out, const CHugeInt& p);
	friend CHugeInt operator+(int n, CHugeInt& p);
	CHugeInt operator+(CHugeInt& p)
	{
		CHugeInt& Max = (this->len > p.len) ? *this : p;
		CHugeInt& Min = (this->len <= p.len) ? *this : p;
		int lmax = (this->len > p.len) ? this->len : p.len;
		int lmin = (this->len <= p.len) ? this->len : p.len;

		int nums[220];
		char temp[220];
		nums[lmax] = 0;
		for (int i = 0; i < lmax; i++)
		{
			if (i < lmin)
			{
				nums[i] = (Max.MaxNums[i] - '0') + (Min.MaxNums[i] - '0');
			}
			else
			{
				nums[i] = Max.MaxNums[i] - '0';
			}
		}
		for (int i = 0; i < lmax - 1; i++)
		{
			nums[i + 1] += nums[i] / 10;
			nums[i] = nums[i] % 10;
			temp[i] = '0' + nums[i];
		}
		if (nums[lmax - 1] >= 10)
		{
			nums[lmax] += nums[lmax - 1] / 10;
			nums[lmax - 1] %= 10;
			temp[lmax - 1] = '0' + nums[lmax - 1];
			temp[lmax] = '0' + nums[lmax];
			lmax++;
		}
		else
		{
			temp[lmax - 1] = '0' + nums[lmax - 1];
		}
		temp[lmax] = '\0';
		CHugeInt t;
		t.len = lmax;
		strcpy(t.MaxNums, temp);
		return t;
	}
	CHugeInt operator+(int& n)
	{
		return CHugeInt(n) + *this;
	}
	CHugeInt& operator+=(int n)
	{
		*this = this->operator+(n);
		return *this;
	}
	CHugeInt& operator++()
	{
		*this += 1;
		return *this;
	}
	CHugeInt operator++(int n)
	{
		CHugeInt temp;
		strcpy(temp.MaxNums, this->MaxNums);
		temp.len = this->len;
		*this += 1;
		return temp;
	}
};
ostream& operator<<(ostream& out, const CHugeInt& p)
{
	for (int i = p.len - 1; i >= 0; i--)
	{
		out << p.MaxNums[i];
	}
	return out;
}
CHugeInt operator+(int n, CHugeInt& p)
{
	return p.operator+(n);
}
int  main()
{
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout << ++b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}