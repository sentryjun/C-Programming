#include <iostream>
using namespace std;

int bitManipulation1(int n, int m, int i) {
// 在此处补充你的代码
    return (m >> i ) & 1 == 1 ? n | (1 << i) : n & (~(1 << i)); 
}

int main() {
	int n, m, i, t;
	cin >> t;
	while (t--) { 
		cin >> n >> m >> i;
		cout << bitManipulation1(n, m, i) << endl;
	}
	return 0;
}