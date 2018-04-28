#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
#include <set>
#include <cstdlib>
#include <cmath>
using namespace std;

int main(int argv, char ** argcs) {
    //char nums[20];
    string nums;
    int n;
    scanf("%d", &n);
    stack<double>st;
    multiset<double>mem;
    double x, y, ans;
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x);
        mem.insert(x);
    }
    while (cin>>nums) {
        if (nums == "+"||nums == "-"||nums == "*"||nums == "/"||nums == "^"){
            x = st.top(); st.pop();
            y = st.top(); st.pop();

            if (nums == "+")ans = x+y;
            else if (nums == "-")ans = y-x;
            else if (nums == "*")ans = y*x;
            else if (nums == "/")ans = y/x;
            else if (nums == "^")ans = pow(y, x);
            st.push(ans);
        }
        else if (nums == "=") {
            ans = st.top(); st.pop();
            printf("%e\n", ans);
            
            mem.erase(mem.begin());
            mem.insert(ans);
        }
        else {
            st.push(stod(nums));
        }
    }
    printf("\n");
    int flag = 1;
    multiset<double>::iterator it = mem.begin();
    for (; it != mem.end(); it++) {
        if (flag % 10 == 0) {
            printf("%e\n", *it);
        }
        else {
            printf("%e ", *it);
        }
        flag++;
    }
    return 0;
}