#include <iostream>
#include <memory.h>
#include <set>
using namespace std;
const int MAX = 30;
const int INF = 9999999;
int wall[MAX][MAX];
int paint[MAX][MAX];
char input[MAX];
int guess(int n, int b)
{
    int s = b;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            paint[i+1][j] = (wall[i][j]+1+paint[i-1][j]+paint[i][j-1]+paint[i][j+1]+paint[i][j])%2;
            if (paint[i+1][j] == 1)s++;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if((paint[n][i-1]+paint[n][i]+paint[n][i+1]+paint[n-1][i])%2 == wall[n][i])
        {
            return INF;
        }
    }
    return s;
}
void enumerate(int n)
{
    int c = 0;
    int b = 0;
    int min_steps = INF;
    set<int>steps;
    int t = 1 << n;
    for(int i = 1; i <= n; i++)
    {
        paint[1][i] = 0;
    }
    while(t--)
    {
        steps.insert(guess(n, b));
        c = 1;
        paint[1][c]++;
        b++;
        
        while(paint[1][c]>1){
            paint[1][c] = 0;
            b--;
            c++;
            paint[1][c]++;
        }
        
    }
    min_steps = *steps.begin();
    if (min_steps == INF)
    {
        cout << "inf" << endl;
    }
    
    else
    {
        cout << min_steps << endl;
    }
    
}
int main (int argc, char** argcs){
    int n;
    //memset(wall, 0, sizeof(wall));
    //memset(paint, 0, sizeof(paint));
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        char t;
        for (int j = 0; j < n; j++)
        {
            cin >> t;
            wall[i][j+1] = (t == 'y')?1:0;
        }
    }
    enumerate(n);
    return 0;
}