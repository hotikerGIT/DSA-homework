#include <string>
#include <iostream>

int main() {
    int t, n;
    std::cin >> t;
    std::string s;

    while (t--) {
        std::cin >> n;
        std::cin >> s;

        std::string result = "";

        int left = 0;
        while (left + 1 < (int)s.size() && s[left] <= s[left + 1]) {
            result += s[left];
            ++left;
        }

        char choice = s[left];
        left++;
        while (left < (int)s.size() && s[left] <= choice) {
            result += s[left];
            ++left;
        }

        result += choice;

        while (left < (int)s.size()) {
            result += s[left];
            ++left;
        }

        std::cout << result << std::endl;
    }
}