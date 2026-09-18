#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        for (int i = 1; i * 2 <= n; ++i) {
            std::cout << i * 2 << ' ' << i * 2 - 1 << ' ';
        }
    }
}