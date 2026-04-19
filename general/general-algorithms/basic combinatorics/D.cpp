#include <iostream>

int main() {
    int n;
    std::cin >> n;

    long long factorial = 1;
    for (int i = 1; i < n + 1; ++i) {
        factorial *= i;
    }

    std::cout << 2 * factorial / (n * n);
}