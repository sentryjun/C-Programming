#include <iostream>
#include <set>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iomanip>

using namespace std;
multiset<int>SET;
const int SIZE = 10000;
set<int> FLAG;
int main(int argv, char** argcs) {
    int n;
    ofstream out("out.txt");
    streambuf *oldbuf = cout.rdbuf(out.rdbuf());
    cin >> n;
    char op[10];
    int elem;
    while (n--) {
        cin >> op; cin >> elem;
        switch(op[2]) {
            case 'd':
            SET.insert(elem);
            FLAG.insert(elem);
            cout << count(SET.begin(), SET.end(), elem) << endl;
            break;
            case 'l':
            cout << count(SET.begin(), SET.end(), elem) << endl;
            SET.erase(elem);
            /*for (multiset<int>::iterator it = SET.begin(); it != SET.end(); it++){
                if (*it == elem) SET.erase(it);
            }*/
            break;
            case 'k':
            if (find(FLAG.begin(), FLAG.end(), elem) != FLAG.end())
            {cout << 1 << " " << count(SET.begin(), SET.end(), elem) << endl;}
            else {cout << "0 0\n";}
            break;
        }
    }
    return 0;
}