#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string s, res;
    std::cin >> s;
    res = s[0];

    for (int i = 1; i < s.size(); ++i) {
        res += "o";
        res += s[i];
    }

    std::cout << res;
}