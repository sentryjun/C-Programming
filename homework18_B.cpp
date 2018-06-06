#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX 10002
#define MMAX 25
#define MAXINT 0x7fffffff
int min_v[MMAX];
int min_s[MMAX];
int N, M;
int ans;
/**
* @param n 剩余最大体积
* @param m 层数
* @param r 当前层最大半径
* @param h 当前层最大提及
* @param s 当前面积
*/

void dfs(int n, int m, int r, int h, int s)
{
	if (m == 0) {
		if (n) return;
		else {
			ans = min(ans, s);
			return;
		}
	}
    //剪枝0
	if (n < 0) return;
	//剪枝1
	if (s + min_s[m] >= ans)return;
	//剪枝2
	if (n < min_v[m]) return;
	//剪枝3
	if (h < m || r < m) return;
	//剪枝4
    int temp = 0;
    for (int i = 0; i < m; i++) {
        temp += (r-i)*(r-i)*(h-i);
    }
    if (temp < n) return;

	for (int i = r; i >= m; i--) {
		if (m == M) s = i * i;
		for (int j = h; j >= m; j--) {
			s += 2 * i * j;
			dfs(n - i * i * j, m - 1, i - 1, j - 1, s);
			s -= 2 * i * j;
		}
	}
}

int main(int argv, char** argcs) {
	cin >> N >> M;
	ans = MAXINT;
	memset(min_v, 0, sizeof(min_v));
	memset(min_s, 0, sizeof(min_s));
	for (int i = 1; i <= M; i++) {
		min_v[i] = min_v[i - 1] + i * i * i;
		min_s[i] = min_s[i - 1] + 2 * i * i;
	}
	dfs(N, M, (int)sqrt((double)(N - min_v[M - 1]) / M) + 1, (N - min_v[M - 1]) / (M*M) + 1, 0);
	if (ans == MAXINT) cout << 0 << endl;
	else cout << ans << endl;
	return 0;
}