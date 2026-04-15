#include <iostream>

int main() {
    int a, b, c, d, t;
    std::cin >> t;

    while (t--) {
        std::cin >> a >> b >> c >> d;
        if (a == b && a == c && a == d) {
            std::cout << "YES\n";
        }

        else {
            std::cout << "NO\n";
        }
    }

    return 0;
}