#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(3);
    int min = 1e9;
    for (int i = 0; i < 3; ++i) {
        std::cin >> a[i];
        min = std::min(min, a[i]);
    }

    std::cout << n - min << '\n';
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}