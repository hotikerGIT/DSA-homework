#include <string>
#include <iostream>

int main() {
    int n;
    std::string s, t;
    std::cin >> n >> s >> t;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == t[i] || t[i] == '*') continue;

        std::cout << "No";
        return 0;
    }

    std::cout << "Yes";
    return 0;
}