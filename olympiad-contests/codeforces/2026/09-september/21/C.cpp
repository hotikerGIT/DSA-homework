#include <iostream>
#include <string>
#include <vector>

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;
    std::vector<int> prefix(n + 1), pref0(n + 1);
    for (int i = 0; i < s.size(); ++i) {
        prefix[i + 1] = prefix[i] + (s[i] == '1');
        pref0[i + 1] = pref0[i] + (s[i] == '0');
    }

    if (s[0] == '1') {
        std::cout << pref0[n] << std::endl;
        return;
    }

    int res = prefix[n];
    for (int i = 0; i < s.size(); ++i) {
        res = std::min(res, prefix[i] + (s[i] != '1') + pref0[n] - pref0[i + 1]);
    }

    std::cout << res << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}