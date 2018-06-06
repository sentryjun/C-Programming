#include <iostream>
#include <cstring>
using namespace std;
#define MAX 10
char matrix[MAX][MAX];
int visited[MAX];
int rowflag[MAX];
int colflag[MAX];
int ans;
int n, k;
void dfs(int x, int col = 0);
int main(int argv, char**argcs) {
    
    while(cin >> n >> k, n >= 0 && k >= 0) {
        memset(matrix, 0, sizeof(matrix));
        memset(colflag, 0, sizeof(colflag));
        memset(rowflag, 0, sizeof(rowflag));
        ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> matrix[i][j];
            }
        }
        dfs(1, 1);
        cout << ans << endl;
    }
}

void dfs(int x, int  col) {
    if(x > k) {
        ans++;
        return;
    }
    if (col > n) return;
    int row;
    for (row = 1; row <= n; row++) {
        if (matrix[row][col] == '#' && rowflag[row] != 1 && (!colflag[col])) {
            rowflag[row] = 1;
            colflag[col] = 1;
            dfs(x + 1, col + 1);
            rowflag[row] = 0;
            colflag[col] = 0;
        }
    }
    dfs(x, col+1);
}