#include <numeric>
#include <iostream>

int main() {
    int a = 336718728;
    int b = 709848696;

    std::cout << (17 < std::gcd(a, b));
}