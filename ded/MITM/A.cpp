#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::vector<long long> first(1 << (n / 2));
    std::vector<long long> second(1 << (n - n / 2));

    for (int i = 0; i < 1 << (n / 2); ++i) {
        long long sum = 0;

        for (int j = 0; j < n / 2; ++j) {
            if (i >> j & 1) sum += a[j];
        }

        first[i] = sum % m;
    }

    for (int i = 0; i < 1 << (n - n / 2); ++i) {
        long long sum = 0;

        for (int j = 0; j < n - n / 2; ++j) {
            if (i >> j & 1) sum += a[j + n / 2];
        }

        second[i] = sum % m;
    }

    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    long long answer = 0;
    for (long long num : first) {
        int target = m - num - 1;

        int index = std::upper_bound(second.begin(), second.end(), target) - second.begin();
        if (index > 0) {
            answer = std::max(answer, num + second[index - 1]);
        }
    }

    std::cout << answer;
}