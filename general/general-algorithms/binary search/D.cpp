#include <iostream>
#include <vector>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);

    int t, n;
    std::cin >> t;

    while (t--) {
        std::cin >> n;

        std::vector<double> pos(n), time(n);

        for (int i = 0; i < n; ++i) {
            std::cin >> pos[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> time[i];
        }

        double left = *std::min_element(pos.begin(), pos.end());
        double right = *std::max_element(pos.begin(), pos.end());

        for (int iter = 0; iter < 1000; ++iter) {
            double middle1 = left + (right - left) / 3.0;
            double middle2 = right - (right - left) / 3.0;
            double value1 = 0;
            double value2 = 0;

            for (int i = 0; i < n; ++i) {
                value1 = std::max(time[i] + std::fabs(pos[i] - middle1), value1);
                value2 = std::max(time[i] + std::fabs(pos[i] - middle2), value2);
            }

            if (value1 < value2) {
                right = middle2;
            }

            else {
                left = middle1;
            }
        }

        std::cout << (left + right) / 2 << std::endl;
    }
}