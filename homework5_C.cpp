#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
// 在此处补充你的代码
    int x;
    int y;
    int **p;
public:
    Array2(int x, int y)
    {
        this->x = x;
        this->y = y;
        p = new int*[x];
        for (int i = 0; i < x; i++)
        {
            p[i] = new int[y];
        }
    }
    Array2()
    {
        x = 0;
        y = 0;
        p = NULL;
    }
    ~Array2()
    {
        for (int i = 0; i < x; i++)
        {
            delete []p[i];
        }
        delete [] p;
    }
    int* const operator[](const int subscript)
    {
        return p[subscript];
    }
    int operator()(int a, int b)
    {
        if (a < x && b < y)
        {
            return p[a][b];
        }
        return 0;
    }
    Array2& operator=(const Array2& array)
    {
        if (array.p != NULL)
        {
            if (p == NULL)
            {
                for (int i = 0; i < x; i++)
                {
                    delete []p[i];
                }
                delete [] p;
            }
            x = array.x;
            y = array.y;
            p = new int*[x];
            for (int i = 0; i < x; i++)
            {
                p[i] = new int[y];
            }
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    p[i][j] = array.p[i][j];
                }
            }
            return *this;
        }
        else 
        {
            x = 0;
            y = 0;
            for (int i = 0; i < x; i++)
            {
                    delete []p[i];
            }
            delete [] p;
            return *this;
        }
    }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}