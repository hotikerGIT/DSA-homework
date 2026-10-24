#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<int, int>> first(3), second(3);
    for (int i = 0; i < 3; ++i) {
        int a, b;
        std::cin >> a >> b;
        first[i] = {a, b};
    }
    for (int i = 0; i < 3; ++i) {
        int a, b;
        std::cin >> a >> b;
        second[i] = {a, b};
    }

    auto check_win = [&](std::pair<int, int> a, std::pair<int, int> b) {
        if (a.first > b.first && a.second > b.second) return true;
        if ((a.first >= b.first * 2 || a.second >= b.second * 2) &&
            !(b.first >= a.first * 2 || b.second >= a.second * 2)) return true;
        return false;
    };

    for (int a = 0; a < 3; ++a) {
        for (int b = 0; b < 3; ++b) {
            for (int c = 0; c < 3; ++c) {
                if (a == b || a == c || b == c) continue;

                bool res = (
                    check_win(first[0], second[a]) &&
                    check_win(first[1], second[b]) &&
                    check_win(first[2], second[c])
                );

                if (res) {
                    std::cout << "YES\n";
                    std::cout << 1 << ' ' << a + 1 << '\n';
                    std::cout << 2 << ' ' << b + 1 << '\n';
                    std::cout << 3 << ' ' << c + 1 << '\n';
                    return 0;
                }
            }
        }
    }
    std::cout << "NO";
    return 0;
}