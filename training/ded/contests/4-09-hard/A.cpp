#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <random>
#define int long long

bool check(std::vector<int> matrix, int n) {
    std::set<int> sums = {};
    int l_diag = 0, r_diag = 0;

    for (int i = 0; i < n; ++ i) {
        l_diag += matrix[i + n * i];
        r_diag += matrix[n - 1 - i + n * i];
    }

    sums.insert(l_diag);
    sums.insert(r_diag);

    for (int i = 0; i < n; ++i) {
        int sum = 0;

        for (int j = 0; j < n; ++j) {
            sum += matrix[j + n * i];
        }

        sums.insert(sum);
    }

    for (int i = 0; i < n; ++i) {
        int sum = 0;

        for (int j = 0; j < n; ++j) {
            sum += matrix[i + n * j];
        }

        sums.insert(sum);
    }

    return sums.size() == (2 * n + 2);
}

signed main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    int n;
    std::cin >> n;
    std::vector<int> a(n * n);
    std::iota(a.begin(), a.end(), 1);

    if (n <= 2) {
        std::cout << "No\n";
        return 0;
    }

    while (!check(a, n)) {
        std::shuffle(a.begin(), a.end(), gen);
    }

    std::cout << "Yes\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << a[j + n * i] << ' ';
        }
        std::cout << '\n';
    }
}
