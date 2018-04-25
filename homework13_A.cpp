#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;
const int SIZE = 10000;
list<int>* RANGE[SIZE];
int main(int argv, char**argcs)
{
    int n;
    //ofstream out("out.txt");
    //streambuf *oldbuf = cout.rdbuf(out.rdbuf());
    cin >> n;
    char op[10];
    int op1, op2;
    for (int i = 0; i < n; i++)
    {
        cin >> op;
        if (op[0] == 'n'){
            cin >> op1;
            RANGE[op1] = new list<int>;
            RANGE[op1]->clear();
        }
        if (op[0] == 'a'){
            cin >> op1 >> op2;
            RANGE[op1]->push_back(op2);
        }
        if (op[0] == 'm'){
            cin >> op1 >> op2;
            RANGE[op1]->merge(*RANGE[op2]);
        }
        if (op[0] == 'u'){
            cin >> op1;
            RANGE[op1]->sort();
            RANGE[op1]->unique();
        }
        if (op[0] == 'o'){
            cin >> op1;
            list<int> & v = *RANGE[op1];
            v.sort();
            list<int>::iterator it = v.begin();
            for (; it != v.end(); it++)
               cout << *it << " ";
            //ostream_iterator<int>output(cout, " ");
            //copy(v.begin(), v.end(), output);
            cout << endl;
        }

    }
    return 0;
}