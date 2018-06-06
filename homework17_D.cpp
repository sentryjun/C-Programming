#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAX 55
#define MAXINT 0x7fffffff

char nums[MAX];

struct bigInter {
	int num[MAX];
	int lenth;
	bigInter() :lenth(0)
	{
		memset(num, 0, sizeof(num));
	}
	bigInter(const char * s, int l) :lenth(l) {
		memset(num, 0, sizeof(num));
		for (int i = 0; i < l; i++) {
			num[lenth - 1 - i] = s[i] - '0';
		}
	}
	bigInter operator+(const bigInter & other) {
		int l = max(lenth, other.lenth);
		bigInter ans;
		int t = 0;
		for (int i = 0; i < l; i++) {
			ans.num[i] = num[i] + other.num[i] + t;
			if (ans.num[i] >= 10) {
				t = 1;
				ans.num[i] %= 10;
			}
			else {
				t = 0;
			}
		}
		if (t > 0) {
			ans.lenth = l + 1;
			ans.num[l] = t;
		}
		else {
			ans.lenth = l;
		}
		return ans;
	}
	bool operator<(const bigInter & n) {
		if (lenth > n.lenth) {
			return false;
		}
		else if (lenth < n.lenth)
			return true;
		else {
			for (int i = lenth - 1; i >= 0; i--) {
				if (num[i] < n.num[i]) {
					return 1;
				}
				else if (num[i] > n.num[i]) {
					return 0;
				}
			}
			return 0;
		}
	}
	friend ostream & operator<<(ostream & out, const bigInter & t) {
		for (int i = t.lenth - 1; i >= 0; i--) {
			out << t.num[i];
		}
		return out;
	}
};
bigInter dp[MAX][MAX];
bigInter num[MAX][MAX];
int makenum(int i, int j) {
	int ans = 0;
	for (int start = i - 1; start <= j - 1; start++) {
		ans = ans * 10 + (nums[start] - '0');
	}
	return ans;
}
int main(int argv, char** argcs) {
	int m;

	bigInter inf;
	inf.lenth = MAX + 1;
	while (cin >> m) {
		memset(num, 0, sizeof(num));
		memset(dp, 0, sizeof(num));
		cin >> nums + 1;
		int n = strlen(nums + 1);
		for (int i = 1; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				num[i][j] = bigInter(nums + i, j - i + 1);
			}
		}
		for (int i = 1; i <= n; i++) {
			dp[0][i] = bigInter(nums + 1, i);
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (j - 1 < i) {
					dp[i][j] = inf;
				}
				else {
					bigInter m = inf;
					for (int k = i; k < j; k++) {
						bigInter t = dp[i - 1][k] + num[k + 1][j];
						if (t < m) m = t;
					}
					dp[i][j] = m;
				}

			}
		}
		cout << dp[m][n] << endl;

	}
	return 0;
}