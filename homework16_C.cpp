#include <iostream>
#include <string>
#include <cstdio>
#include <memory.h>
using namespace std;
const int MAX_H = 1 << 10;
const int MAX_W = 1 << 11;
char matrix[MAX_H][MAX_W];
void print(int x, int y, int size)
{
    if (size == 1)
    {
        matrix[x][y+1]='/';
		matrix[x][y+2]='\\';
		matrix[x+1][y]='/';
		matrix[x+1][y+3]='\\';
		matrix[x+1][y+1]=matrix[x+1][y+2]='_';
        return;
    }
    print(x, y + (1 << size - 1), size-1);
    print(x + (1 << size - 1), y, size-1);
    print(x + (1 << size -1), y + (1 << size), size - 1);
}
int main(int argv, char**argcs)
{
    int size;
    while (cin >> size, size)
    {
        memset(matrix, ' ', sizeof(matrix));
        print(0, 0, size);
        for (int i = 0; i < (1<<size); i++)
        {
            for (int j = 0; j < (2 << size); j++)
            {
                cout << matrix[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}