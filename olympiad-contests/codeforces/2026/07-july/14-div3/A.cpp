#include <iostream>
#include <string>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::string s;
        std::cin >> n >> s;


        int max = 0;
        int cur = 0;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '#') cur++;
            else {
                max = std::max(max, cur);
                cur = 0;
            }
        }

        max = std::max(max, cur);
        std::cout << (max + 1) / 2 << '\n';
    }
}