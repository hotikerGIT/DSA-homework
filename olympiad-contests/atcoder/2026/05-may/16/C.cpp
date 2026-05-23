#include <iostream>
#include <string>
#include <vector>
#define int long long

signed main() {
    std::string s;
    std::cin >> s;

    int ans = 0;
    for (int index = 0; index < (int)s.size(); ++index) {
        if (s[index] != 'C') continue;

        ans += std::min(index + 1, (int)s.size() - index);
    }

    std::cout << ans;
}