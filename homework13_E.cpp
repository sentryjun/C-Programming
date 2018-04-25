#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cmath>
using namespace std;
class A {
    public:
    int id, force;
    A(){id = 0; force = 0;}
    A(int i, int f):id(i),force(f){};
    friend bool operator<( const A & b, const A & a) {
        return b.force < a.force;
    }
    friend ostream& operator<<(ostream & o, const A & a) {
        o << a.id;
        return o;
    }

};
set<A>SET;
typedef set<A>::iterator AIT;
int main(int argv, char** argcs) {
    int N;
    //fstream out("out.txt");
    //streambuf *oldbuf = cout.rdbuf(out.rdbuf());
    cin >> N;
    SET.insert(A(1, 1000000000));
    set<pair<int, int> >::iterator it;
    for (int i = 1; i <= N; i++) {
        int id, force;
        cin >> id >> force;
        AIT it = SET.insert(A(id, force)).first;
        if (it == SET.begin()) {cout << *it << " " ; it++; cout << *(it) << endl;}
        else {
            AIT iit = --it;
            it++;
            AIT bit = ++it;
            it--;
            if (bit == SET.end())cout << *it << " " << *iit << endl;
            else {
                if (it->force - iit->force <= bit->force - it->force) cout << *it << " " << *iit << endl;
                else cout << *it << " " << *bit << endl;
            }
        }
    }
    return 0;
}