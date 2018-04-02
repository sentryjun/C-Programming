#include <iostream>
using namespace std;
class MyCin
{
// 在此处补充你的代码
    bool flag;
public:
MyCin()
{
    flag = 1;
}
    MyCin& operator>>(int& n)
    {   
        if (flag == 1)
        {
            if (cin >> n) 
            {
                flag = 1;
                if (n < 0)flag = 0;            
            }
            else flag = 0;
        }
        return *this;
    }
    operator bool()
    {
        return flag;    
    }
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}