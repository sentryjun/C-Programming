#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;
const int MAX = 101;
char exps[MAX];
char EXP[MAX];
int s;
bool get_exp_value();
bool get_value();
int main(int argv, char**argcs)
{
    int num = 0;
    while (cin.getline(exps, MAX))
    {
        num++;
        s = 0;
        int ind = 0;
        memset(EXP, 0, sizeof(EXP));
        for (int i = 0; exps[i] != '\0'; i++)
        {
            if (exps[i] == ' ')
            {
                continue;
            }
            EXP[ind++] = exps[i];
        }
        EXP[ind] = '\0';
        cout << "Expression " << num << ": "; 
        if (get_exp_value())
        {
            cout << 'V' << endl;
        }
        else 
        {
            cout << "F" << endl;
        }
    }
    return 0;
}
bool get_exp_value()
{
    bool var = get_value();
    while(true)
    {
        if (EXP[s] == '|' || EXP[s] == '&')
        {
            char op = EXP[s];
            s++; 
            bool t = get_value();
            if (op == '|')
            {
               var = var | t;
            }
            else 
            {
                var = var & t;
            }
        }
        
        else
        {
            break;
        }
    }
    return var;
}
bool get_value()
{
    char temp = EXP[s];
    bool var = 1;
    if (temp == 'V')
    {
        var = 1;
        s++;
    }
    else if (temp == 'F')
    {
        var = 0;
        s++;
    }
    else if (temp == '(')
    {
        s++;
        var = get_exp_value();
        s++;
    }
    else if (temp == '!')
    {
        s++;
        var = !get_value();
    }
    return var;
}