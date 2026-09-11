#include <iostream>

int power(int base, int exponent, int mod) {
    if (exponent == 0) return 1;

    if (exponent % 2 == 0) {
        return power((base * base) % mod, exponent / 2, mod) % mod;
    }

    return (base * power(base, exponent - 1, mod)) % mod;
}

int reverse_mod(int num, int mod) {
    return power(num, mod - 2, mod);
}

int main() {
    std::cout << reverse_mod(2, 101);
}