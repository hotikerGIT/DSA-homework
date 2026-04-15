#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    long long k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());

    long long difference = a[n - 1] - a[0];

    std::vector<int> delta(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        delta[i] = a[i + 1] - a[i];
    }

    std::vector<int> income_prefix(n / 2);
    std::vector<long long> cost_prefix(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        cost_prefix[i] = (i + 1) * delta[i];
        income_prefix[i] = delta[i];

        if (i != n - i - 2) {
            cost_prefix[i] += (i + 1) * delta[n - i - 2];
            income_prefix[i] += delta[n - i - 2];
        }

        if (i != 0) {
            cost_prefix[i] += cost_prefix[i - 1];
            income_prefix[i] += income_prefix[i - 1];
        }
    }

    int left = 0;
    int right = (int)cost_prefix.size() - 1;
    int middle;

    while (left <= right) {
        middle = (left + right) / 2;

        if (cost_prefix[middle] < k) {
            left = middle + 1;
        }

        else {
            right = middle - 1;
        }
    }

    long long jump = income_prefix[right];
    k -= cost_prefix[right];
    jump += k / (right + 2);

    difference = std::max(difference - jump, (long long)0);
    std::cout << difference;
}