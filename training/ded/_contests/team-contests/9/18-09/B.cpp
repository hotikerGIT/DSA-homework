#include <iostream>
#define int long long

int factorial(int n) {
    int res = 1;

    for (int i = 1; i <= n; ++i) {
        res *= i;
    }

    return res;
}

signed main() {
    int n;
    std::cin >> n;

    int res = factorial((n + 1) / 2);
    res *= factorial(n - (n + 1) / 2);
    std::cout << res;
}