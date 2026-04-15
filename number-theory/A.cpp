#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    int a, b, q;
    std::cin >> a >> b >> q;

    int g = std::__gcd(a, b);
    std::vector<int> divisors;
    for (int i = 1; i * i <= g; ++i) {
        if (g % i == 0) {
            divisors.push_back(i);
            if (i != g / i) divisors.push_back(g / i);
        }
    }

    std::sort(divisors.begin(), divisors.end());

    while (q--) {
        int low, high;
        std::cin >> low >> high;

        auto it = std::upper_bound(divisors.begin(), divisors.end(), high);

        int out = -1;
        if (it != divisors.begin()) {
            it--;
            int ans = *it;
            if (ans >= low) out = ans;
        }

        std::cout << out << std::endl;
    }
}