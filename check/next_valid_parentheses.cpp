#include <iostream>
#include <string>

using namespace std;

string next_valid(string s) {
    int n = s.size();
    int balance = 0;

    for (int i = n - 1; i > 0; --i) {
        if (s[i] == '(') balance--;
        else balance++;

        if (s[i] == '(' && balance > 0) {
            s[i] = ')';

            int prefix_open = 0;
            for (int j = 0; j < i; ++j) if (s[j] == '(') prefix_open++;

            int need_open = n / 2 - prefix_open;

            for (int open = 0; open < need_open; ++open) {
                s[i + 1 + open] = '(';
            }

            for (int closed = i + 1 + need_open; closed < n; ++closed) {
                s[closed] = ')';
            }

            return s;
        }
    }

    return "";
}

int main() {
    string s = "((((()))))";
    string res = s;

    while (!res.empty()) {
        cout << res << endl;
        res = next_valid(res);
    }
}