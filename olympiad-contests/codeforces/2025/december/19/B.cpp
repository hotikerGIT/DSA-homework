#include <iostream>
#include <vector>
#include <string>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::string cur;

        for (int i = 0; i < n; ++i) {
            std::string s;
            std::cin >> s;

            cur = std::min(cur + s, s + cur);
        }

        std::cout << cur << std::endl;
    }
}