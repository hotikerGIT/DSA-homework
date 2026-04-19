#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    if (m < n) std::swap(n, m);

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(1 << n));

}