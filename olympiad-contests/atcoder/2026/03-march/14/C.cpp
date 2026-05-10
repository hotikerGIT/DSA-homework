#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define int long long

signed main() {
    int n, l, r;
    std::cin >> n >> l >> r;
    std::string s;
    std::cin >> s;

    std::vector<std::vector<int>> chars(26, std::vector<int>());
    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        chars[c - 'a'].push_back(i);
    }

    int ans = 0;
    for (char c = 0; c < 26; ++c) {
        for (int index : chars[c]) {
            ans += (int)(std::upper_bound(chars[c].begin(), chars[c].end(), index + r) -
                    std::lower_bound(chars[c].begin(), chars[c].end(), index + l));
        }
    }

    std::cout << ans;
}