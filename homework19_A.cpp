#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int MAX = 65535;
const int MAXN = 16;
char maze[MAXN];
bool mark[1 << 16];
int STATE = 0;
int ans = 0;
typedef pair<int, int> Node;
void bfs() {
    queue<Node> q;
    q.push(Node(STATE, 0));
    Node temp, nex;
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        if (temp.first == MAX || temp.first == 0) {
            ans = temp.second;
            return;
        }
        for (int i = 0; i < MAXN; i++) {
            int t = temp.first;
            t ^= (1 << i);
            //上下左右
            if (i >= 4) t ^= (1 << (i-4));
            if (i < 12) t ^= (1 << (i+4));
            if (i % 4 != 0) t ^= (1 << (i-1));
            if ((i+1) % 4 != 0) t ^= (1 << (i+1));
            nex = Node(t, temp.second+1);
            if(!mark[nex.first]) {
                mark[nex.first] = 1;
                q.push(nex);
            }
        }
    }
    ans = -1;
}
int main(int argv, char**argcs) {
    for (int i = 0; i < MAXN; i++) {
        cin >> maze[i];
    }
    for (int i = 0; i < MAXN; i++) {
        if (maze[i] == 'w')
            STATE |= (1 << i);
    }
    bfs();
    if (ans < 0) {
        printf("Impossible\n");
    }
    else {
        cout << ans << endl;
    }
}