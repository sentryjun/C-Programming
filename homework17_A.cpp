#include <iostream>
#include <memory.h>

using namespace std;
const int MAX = 251;
unsigned int dp[MAX][MAX];
unsigned int ans[MAX];
void cal(int n) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i <= n; i++) {
            dp[0][i] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j<= i; j++) {
                dp[i][j] = 1;
            }
        }
        for (int i = 2; i <= n; i++) {
            for (int j = i/2; j >= 1; j--) {
                dp[i][j] = dp[i - 2 * j][j] + dp[i][j+1];
            }
        }
}
int main(int argv, char**argcs) {
    int n;
    cal(250);
    while(cin >> n, n) {  
        cout << n << " "<< dp[n][1] << endl;
    }
}