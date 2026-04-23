#include <iostream>
#include <string>
#define int long long

int char_to_b64(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'Z') return c - 'A' + 10;
    if ('a' <= c && c <= 'z') return c - 'a' + 36;
    if (c == '-') return 62;
    if (c == '_') return 63;
    return -1;
}

signed main() {
    std::string s;
    std::cin >> s;

    int ans = 1;
    for (char c : s) {
        int num = char_to_b64(c);

        for (int j = 0; j < 6; ++j) {
            int bit = (num >> j) & 1;
            ans *= bit ? 1 : 3;
            ans %= (int)1e9 + 7;
        }
    }

    std::cout << ans;
}