#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;
string STR[501];
int find(), rfind();
string copy(), add();
bool IsNum(string & s1, string & s2) {
    if (s1.length() > 5 || s2.length() > 5) {
        return false;
    }
    for (int i = 0; i < s1.length(); i++) { if (isalpha(s1[i])) return false; }
    for (int i = 0; i < s2.length(); i++) { if (isalpha(s2[i])) return false; }
    return 1;
}
int find() {
    string temp, s; int N;
    cin >> temp;
    if (temp == "copy")
    {
        s = copy();
    }
    else if (temp == "add")
    {
        s = copy();
    }
    else s = temp;
    cin >> temp;
    if (temp == "find") N = find();
    else if (temp == "rfind") N = rfind();
    else  N = stoi(temp);
    int n = STR[N].find(s);
    if (n == string::npos)
    {
        return s.length();
    }
    return n;
}
int rfind() {
    string temp, s; int N;
    cin >> temp;
    if (temp == "copy")
    {
        s = copy();
    }
    else if (temp == "add")
    {
        s = copy();
    }
    else s = temp;
    cin >> temp;
    if (temp == "find") N = find();
    else if (temp == "rfind") N = rfind();
    else  N = stoi(temp);
    int n = STR[N].rfind(s);
    if (n == string::npos)
    {
        return s.length();
    }
    return n;
}
string copy() {
    string temp;
    int N, X, L;
    cin >> temp;
    if (temp == "find") N = find();
    else if (temp == "rfind") N = rfind();
    else N = stoi(temp);
    cin >> temp;
    if (temp == "find") X = find();
    else if (temp == "rfind") X = rfind();
    else X = stoi(temp);
    cin >> temp;
    if (temp == "find") L = find();
    else if (temp == "rfind") L = rfind();
    else L = stoi(temp);
    return STR[N].substr(X, L);
}
string add() {
    string temp, S1, S2;
    cin >> temp;
    if (temp == "copy")
    {
        S1 = copy();
    }
    else if (temp == "add")
    {
        S1 = add();
    }
    else S1 = temp;
    cin >> temp;
    if (temp == "copy")
    {
        S2 = copy();
    }
    else if (temp == "add")
    {
        S2 = add();
    }
    else S2 = temp;
    if (IsNum(S1, S2)) return to_string(stoi(S1) + stoi(S2));
    return (S1 + S2);
}
void insert() {
    string temp, s; int N, X;
    cin >> temp;
    if (temp == "copy")
    {
        s = copy();
    }
    else if (temp == "add")
    {
        s = add();
    }
    else s = temp;
    cin >> temp;
    if (temp == "find") N = find();
    else if (temp == "rfind") N = rfind();
    else N = stoi(temp);
    cin >> temp;
    if (temp == "find") X = find();
    else if (temp == "rfind") X = rfind();
    else X = stoi(temp);
    STR[N].insert(X, s);
}
void reset() {
    string temp, s; int N;
    cin >> temp;

    if (temp == "copy")
    {
        s = copy();
    }
    else if (temp == "add")
    {
        s = add();
    }
    else s = temp;
    cin >> temp;
    if (temp == "find") N = find();
    else if (temp == "rfind") N = rfind();
    else N = stoi(temp);
    STR[N] = s;
}
void print() {
    string temp; int N;
    cin >> temp;
    if (temp == "find") N = find();
    else if (temp == "rfind") N = rfind();
    else N = stoi(temp);
    cout << STR[N] << endl;
}
int main(int argv, char** argcs) {
    int n;
    cin >> n;
    ofstream out("out.txt");
    streambuf *oldbuf = cout.rdbuf(out.rdbuf());
    for (int i = 1; i <= n; i++)cin >> STR[i];
    string op;
    string op1, op2, op3;
    while (true) {
        cin >> op;
        if (op == "copy") copy();
        else if (op == "add") add();
        else if (op == "find") find();
        else if (op == "rfind") rfind();
        else if (op == "insert") insert();
        else if (op == "reset") reset();
        else if (op == "print") print();
        else if (op == "printall") {
            for (int var = 1; var <= n; var++)cout << STR[var] << endl;
        }
        else if (op == "over") break;
    }
    return 0;
}