#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int maze[5][5] = {

0, 1, 0, 0, 0,

0, 1, 0, 1, 0,

0, 0, 0, 0, 0,

0, 1, 1, 1, 0,

0, 0, 0, 1, 0,

};
typedef pair<int, int> Point;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
bool mark[6][6];
Point rec[6][6];
void bfs() {
    queue<Point>q;
    Point temp, nex;
    int x, y;
    temp = Point(4, 4);
    q.push(temp);
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        if (temp.first == 0 && temp.second == 0) {
            break;
        }
        
        for (int i = 0; i < 4; i++) {
            x = temp.first + dx[i];
            y = temp.second + dy[i];
            if (x < 0 || y < 0 || x > 4 || y > 4) {
                continue;
            }
            if (!mark[x][y] && !maze[x][y]) {
                nex = Point(x, y);
                rec[x][y] = Point(temp.first, temp.second);
                q.push(nex);
                mark[x][y] = 1;
            }
        }
    }
}
int main(int argv, char**argcs) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> maze[i][j];
        }
    }
    bfs();
    int a = 0, b = 0, i, j;
    printf("(0, 0)\n");
    while (a != 4 || b != 4) {
        i = rec[a][b].first;
        j = rec[a][b].second;
        a = i;
        b = j;
        printf("(%d, %d)\n", i, j);
    }
}