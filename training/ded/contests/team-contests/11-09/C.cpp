#include <iostream>
#include <string>

int main() {
    int n;
    std::string s;
    std::cin >> n >> s;

    int big_cnt = 0;
    int small_cnt = 0;

    for (char c : s) {
        big_cnt += 'X' == c;
        small_cnt += 'x' == c;
    }

    if (big_cnt == small_cnt) {
        std::cout << 0 << '\n';
        std::cout << s;
        return 0;
    }

    int ans = 0;
    if (big_cnt < small_cnt) {
        int diff = (small_cnt - big_cnt) / 2;
        ans = diff;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'x' && diff > 0) {
                s[i] = 'X';
                diff--;
            }
        }
    } else {
        int diff = (big_cnt - small_cnt) / 2;
        ans = diff;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'X' && diff > 0) {
                s[i] = 'x';
                diff--;
            }
        }
    }

    std::cout << ans << '\n';
    std::cout << s;
}