#include <iostream>
#include <memory.h>
#include <set>
#include <vector>
using namespace std;

const int OPS[10][9] = {
    {},
    {1,1,0,1,1,0,0,0,0},  
               {1,1,1,0,0,0,0,0,0}, 
               {0,1,1,0,1,1,0,0,0},  
               {1,0,0,1,0,0,1,0,0},  
               {0,1,0,1,1,1,0,1,0},  
               {0,0,1,0,0,1,0,0,1},  
               {0,0,0,1,1,0,1,1,0},  
               {0,0,0,0,0,0,1,1,1},  
               {0,0,0,0,1,1,0,1,1} 
};
int clocks[10];
int temp[10];
int op[10];


int main(int argc, char**argv)
{
    for (int i = 1; i < 10; i++)
        cin >> clocks[i];
    for (int i = 1; i < 10; i++)
    {
        if (clocks[i] != 0)
        {
            break;
        }
        if (i == 9 && clocks[i]==0)
        {
            return 0;
        }
    }
    int min_num = 0xfffff, t;
    int op1, op2, op3, op4, op5, op6, op7, op8, op9;
    for (op1 = 0; op1 <= 3; op1++)
    {
        for (op2 = 0; op2 <= 3; op2++)
        {
            for (op3 = 0; op3 <= 3; op3++)
            {
                for (op4 = 0; op4 <=3; op4++)
                {
                    for (op5 = 0; op5 <= 3; op5++)
                    {
                        for (op6 = 0; op6 <= 3; op6++)
                        {
                            for (op7 = 0; op7 <= 3; op7++)
                            {
                                for (op8 = 0; op8 <= 3; op8++)
                                {
                                    for (op9 = 0; op9 <= 4; op9++)
                                    {
                                        int flag = 0;
                                        for (int i = 0; i < 9; i++)
                                        {
                                            t = clocks[i+1]+ op1*OPS[1][i] + op2 * OPS[2][i] + op3 * OPS[3][i]+op4 * OPS[4][i]+op5 * OPS[5][i]+op6 * OPS[6][i]+op7 * OPS[7][i]+op8 * OPS[8][i]+op9 * OPS[9][i];
                                            t %= 4;
                                            if (t) flag = 1;
                                        }
                                        if (flag == 0)
                                        {
                                            int num = op1+op2+op3+op4+op5+op6+op7+op8+op9;
                                            if (num < min_num)
                                            {
                                                min_num = num;
                                                op[1] = op1;
                                                op[2] = op2;
                                                op[3] = op3;
                                                op[4] = op4;
                                                op[5] = op5;
                                                op[6] = op6;
                                                op[7] = op7;
                                                op[8] = op8;
                                                op[9] = op9;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        while(op[i]--)
        {
            cout << i << ' ';
        }
    }
    cout << endl;
    return 0;
}