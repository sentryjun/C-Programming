#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 101;
int dp[MAX][MAX];
int board[MAX][MAX];
int R, C;
const int X[] = {0, 0, 1, -1};
const int Y[] = {1, -1, 0, 0};
int dfs(int x, int y);
bool isValid(int i, int j);
int main(int argc, char ** argv) {
    cin >> R >> C;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> board[i][j];
        }
    }
    int maxLen = 0;
    for (int i = 1; i <= R; i++ ){
        for (int j = 1; j <= C; j++) {
            dp[i][j] = dfs(i, j);
            if (maxLen < dp[i][j]) {
                maxLen = dp[i][j];
            }
        }
    }
    cout << maxLen + 1 << endl;
}
int dfs(int x, int y) {
    if (dp[x][y])
    {
        return dp[x][y];
    }
    for (int i = 0; i < 4; i++)
    {
        int nextX = x + X[i];
        int nextY = y + Y[i];
        if (isValid(nextX, nextY) && board[nextX][nextY] < board[x][y]) {
            int temp = dfs(nextX, nextY) + 1;
            dp[x][y] = max(dp[x][y], temp);
        }
    }
    return dp[x][y];
}
bool isValid(int i, int j) {
    return (i >= 1 && i <= R && j >= 1 && j <= C);
}