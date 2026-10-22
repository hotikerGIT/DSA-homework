#include <vector>
#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input;
    std::cin >> input;
    std::string s;
    s.reserve(input.size());
    for (char c : input) {
        if (s.empty() || s.back() != c) s.push_back(c);
    }

    int L = 2;
    while (true) {
        int n = (int)s.size();
        if (2 * L > n) break;

        bool found = false;

        for (int i = 0; i + 2 * L <= n; ++i) {
            bool eq = true;

            for (int k = 0; k < L; ++k) {
                if (s[i + k] != s[i + L + k]) {
                    eq = false;
                    break;
                }
            }

            if (eq) {
                s.erase(i + L, L);
                found = true;
                break;
            }
        }

        L += !found;
    }

    std::cout << s << '\n';
}