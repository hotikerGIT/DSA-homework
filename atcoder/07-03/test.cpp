#include <iostream>

int main() {
    int n = 316227766;
    int m = 7;
    int m1 = 7148;
    int mod = 10007;
    std::cout << ((n + m - 1) * m1) % mod;
}