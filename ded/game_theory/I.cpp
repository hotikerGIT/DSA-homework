#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int nim_sum = 0;
    for (int i = 0 ; i < n; ++i) {
        int a;
        std::cin >> a;
        nim_sum ^= a;
    }

    std::cout << (nim_sum == 0 ? "Vasya" : "Petya");
}