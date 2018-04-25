#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <memory>

using namespace std;
int PRIME[1000] = {0};
bool PRIMES[3200] = {0};
int VAR = 0;
int START = 1;
int END = 1;
typedef pair<int, int> K;

int IsPrime(int n) {
    if (n == 2) return 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}


void get_prime() {
    int t = sqrt(10000000);
    for (int i = 2; i <= t; i++) {
        if (!PRIMES[i]) {
            if (IsPrime(i)) {
                for (int j = i + i; j <= t; j += i) {
                    PRIMES[j] = 1;
                }
            }
        }
    }
    VAR = 0;
    for (int i = 2; i <= t; i++) {
        if (!PRIMES[i]) PRIME[VAR++] = i;
    }
}

int get_Prime_num(int n) {
    int ans = 0, total = n;
    for (int i = 0; i < VAR; i++) {
        if (PRIME[i] >= n) break;
        if (total % PRIME[i] == 0) {
            ans++;
            while (total % PRIME[i] == 0) {
                total /= PRIME[i];
            }
        }
    }
    return ans;
}

struct MyLess {
    bool operator()(K &t1, K &t2) {
        int a = t1.first, b = t2.first;
        if (a < b) return 1;
        else if (a == b) { return t1.second < t2.second; }
        return 0;
    }
};

struct MyGreater {
    bool operator()(K &T1, K &T2) {
        return !MyLess()(T1, T2);
    }
};

int main(int argv, char **argcs) {
    int num;
    PRIMES[0] = 1;
    PRIMES[1] = 1;
    scanf("%d", &num);
    VAR = 0;
    get_prime();
    vector<K> temp;
    priority_queue<int, vector<pair<int, int> >, MyLess> big_queue;
    priority_queue<int, vector<pair<int, int> >, MyGreater> little_queue;
    for (int i = 0; i < num; i++) {
        for (int m = 0; m < temp.size(); m++) {
            big_queue.push(temp[m]);
            little_queue.push(temp[m]);
        }
        temp.clear();
        for (int t = 0; t < 10; t++) {
            int tm;
            cin >> tm;
            big_queue.push(make_pair(get_Prime_num(tm), tm));
            little_queue.push(make_pair(get_Prime_num(tm), tm));
        }
        cout << big_queue.top().second << " " << little_queue.top().second << endl;
        big_queue.pop();
        little_queue.pop();
        for (int j = 0; j < 9; j++) {
            temp.push_back(big_queue.top());
            big_queue.pop();
            little_queue.pop();
        }
        temp.pop_back();
    }
    return 0;
}