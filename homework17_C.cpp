#include <iostream>
#include <memory.h>
using namespace std;
const int MAX_N = 200;
const int MAX_X = 10002;
int dp1[MAX_X], dp2[MAX_X], coins[MAX_N], ans[MAX_N];
int flag = 0;

int main(int argv, char**argcs) {
    int n, x;
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> coins[i];
    }
    dp1[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = x; j >= coins[i]; j--) {
            dp1[j] += dp1[j - coins[i]];
        }
    }
    for (int i = 1; i <= n; i++) {
        memset(dp2, 0, sizeof(dp2));
        for (int j = 0; j <= x; j++) {
            
            if (j - coins[i] >= 0) {
                dp2[j] = dp1[j] - dp2[j-coins[i]];
            }
            else {
                dp2[j] = dp1[j];
            }
        }
        if (dp2[x] == 0)ans[flag++] = coins[i];

    }
    cout << flag << endl;
    for (int i = 0; i < flag; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}