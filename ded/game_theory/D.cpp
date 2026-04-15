#include <iostream>
#include <string>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        std::string s;
        std::cin >> s;

        int cnt0 = 0;
        int cnt1 = 0;

        for (auto c : s) {
            cnt0 += c == '0';
            cnt1 += c == '1';
        }

        std::cout << (std::min(cnt0, cnt1) % 2 ? "DA" : "NET") << '\n';
    }
}