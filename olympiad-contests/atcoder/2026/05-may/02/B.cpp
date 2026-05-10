#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> a(3, std::vector<int>(6));
    std::vector p(3, std::vector<double>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 6; ++j) {
            std::cin >> a[i][j];

            if (a[i][j] > 3) {
                p[i][a[i][j] - 4] += 1.0 / 6;
            }
        }
    }

    double ans = 0;
    ans += p[0][0] * (p[1][1] * p[2][2] + p[1][2] * p[2][1]);
    ans += p[0][1] * (p[1][0] * p[2][2] + p[1][2] * p[2][0]);
    ans += p[0][2] * (p[1][0] * p[2][1] + p[1][1] * p[2][0]);

    std::cout << ans;
}