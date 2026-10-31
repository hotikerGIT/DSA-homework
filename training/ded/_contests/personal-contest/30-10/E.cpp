#include <iostream>

int main() {
    int n;
    std::cin >> n;

    double cur_min = 1e9;
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        double a;
        std::cin >> a;
        cur_min = std::min(a, cur_min);

        ans = std::max(ans, a - cur_min);
    }

    std::cout << ans;
}