#include <iostream>
#include <cmath>
#include <numbers>
#include <iomanip>

int main() {
    int n, r;
    std::cin >> n >> r;

    double angle = std::numbers::pi / n;
    double t = 2 * std::sin(angle);
    double ans = r * t / (2 - t);

    std::cout << std::fixed << std::setprecision(6) << ans;
}