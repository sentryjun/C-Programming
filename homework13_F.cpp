#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
#include <cstdio>
//#include <fstream>
//#include <cmath>

using namespace std;
typedef pair<int, int> A;

class MyLess {
    bool operator()(const A &a, const A &b) {
        return a.second < b.second;
    }
};

set<pair<int, int>> SET;

typedef set<A>::iterator AIT;

int main(int argv, char **argcs) {
    int N;
    //fstream out("out.txt");
    //streambuf *oldbuf = cout.rdbuf(out.rdbuf());
    scanf("%d", &N);
    SET.insert(make_pair(1000000000, 1));
    for (int i = 1; i <= N; i++) {
        int id, force;
        //cin >> id >> force;
        scanf("%d %d", &id, &force);
        auto it = SET.lower_bound(make_pair(force, -1));
        auto temp = it;
        if (it != SET.end()) {
            temp = it;
        }
        if (it != SET.begin()) {
            it--;
            it = SET.lower_bound(make_pair(it->first, -1));
            if (force - it->first < temp->first - force || (force - it->first == temp->first - force && it->second < temp->second)) {
                temp = it;
            }
        }
        SET.insert(make_pair(force, id));
        //cout << id << " " << temp->second << endl;
        printf("%d %d\n", id, temp->second);
    }
    return 0;
}