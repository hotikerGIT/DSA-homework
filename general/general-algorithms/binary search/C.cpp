#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    long long total = 1LL * n * (n + 1) / 2;

    vector<int> run;
    for (int i = 0; i < n; ) {
        int j = i + 1;

        while (j < n && s[j] == s[i]) {
            ++j;
        }

        run.push_back(j - i);
        i = j;
    }

    long long bad = n;
    for (int i = 0; i + 1 < (int)run.size(); ++i) {
        bad += (long long)run[i] + run[i+1] - 1;
    }

    long long good = total - bad;
    cout << good;
    return 0;
}

