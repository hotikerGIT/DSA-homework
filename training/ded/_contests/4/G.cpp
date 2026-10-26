#include <iostream>
#include <vector>

int main() {
    freopen("suffixgame.in", "r", stdin);
    freopen("suffixgame.out", "w", stdout);
    int n;
    std::cin >> n;
    std::vector a(n + 1, 0);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    long long turns = 0;
    for (int i = n; i > 0; --i) turns += a[i] - a[i - 1] - 1;
    if (turns % 2 == 0) std::cout << "Second";
    else std::cout << "First";
}