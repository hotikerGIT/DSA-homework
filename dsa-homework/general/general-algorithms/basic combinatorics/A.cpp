#include <iostream>
#include <string>

int main() {
    int t;
    std::string s;
    std::cin >> t;

    while (t--) {
        std::cin >> s;

        int res = (s[0] - 'a') * 25;
        res += (s[1] > s[0]) ? (s[1] - 'a' - 1) : (s[1] - 'a');

        std::cout << res + 1 << std::endl;
    }
}