#include <iostream>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::cout << (n % 2 == 0 ? 1 : 0) << '\n';
    }
}