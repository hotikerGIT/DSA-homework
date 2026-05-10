#include <iostream>

long long binpow(long long a, long long b, long long MOD) {
    long long res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long modinv(long long a, long long MOD) {
    return binpow(a, MOD - 2, MOD);
}

long long C(int n, int k, int MOD) {
    if (k > n - k) k = n - k;
    long long num = 1, den = 1;

    for (int i = 1; i <= k; i++) {
        num = num * (n - k + i) % MOD;
        den = den * i % MOD;
    }
    return num * modinv(den, MOD) % MOD;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::cout << C(n + m - 1, n, 998244353);
}