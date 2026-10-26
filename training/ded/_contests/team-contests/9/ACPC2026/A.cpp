#include <iostream>
#include <vector>
#include <string>

int main() {
    int n, m;
    std::cin >> n;
    std::vector<std::string> init(n);
    for (int i = 0; i < n; ++i) std::cin >> init[i];
    std::cin >> m;
    std::vector<std::string> broad(m);
    for (int i = 0; i < m; ++i) std::cin >> broad[i];

    int ans = 0;

    for (auto& s : broad) {
        if (s[0] != 'G') continue;

        for (auto& check : init) {
            if (check.substr(1, check.size() - 1) == s.substr(1, s.size() - 1)) {
                ans++;
                break;
            }
        }
    }

    std::cout << ans;
}