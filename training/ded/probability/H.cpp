#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    int n, p;
    std::cin >> n >> p;

    std::vector<double> prob(n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;

        int first_good = l;
        if (first_good % p != 0) first_good += p - first_good % p;
        double good = 0;
        if (first_good <= r) good++;
        good += std::max(0, (r - first_good) / p);

        prob[i] = good / (r - l + 1);
    }

    double ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        ans += 2000 * (1 - (1 - prob[i]) * (1 - prob[j]));
    }

    std::cout << std::fixed << std::setprecision(6) << ans;
}