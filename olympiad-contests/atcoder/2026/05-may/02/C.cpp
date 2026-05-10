#include <iostream>
#include <vector>
#include <string>
#define int long long

signed main() {
    std::string s;
    std::cin >> s;
    int n = s.size();

    int ans = n;
    int left = 0, right = 1;
    while (right < n) {
        int len = 1;
        while (right < n && s[right - 1] != s[right]) {
            len++;
            right++;
        }

        ans += len * (len - 1) / 2;
        right++;
    }

    std::cout << ans % 998244353;
}