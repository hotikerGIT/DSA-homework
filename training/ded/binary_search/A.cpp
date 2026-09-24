#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double c;
    std::cin >> c;

    double left = 0;
    double right = 1e5;
    double eps = 1e-7;
    double ans = 0;
    while (right - left > eps) {
        double mid = (left + right) / 2;

        if (mid * mid + sqrt(mid) < c) {
            left = mid + eps;
        } else {
            right = mid - eps;
        }
    }

    std::cout << std::fixed << std::setprecision(6) << left << std::endl;
}