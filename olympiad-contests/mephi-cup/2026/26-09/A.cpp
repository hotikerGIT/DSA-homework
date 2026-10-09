#include <iostream>
#include <vector>
#define int long long

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::vector<int> diff(n - 1);
    for (int i = 0; i < n - 1; ++i) diff[i] = a[i + 1] - a[i];

    int left = -1, right = 0;
    int left_zero = -1;
    bool is_good = true;
    for (int i = 0; i < n - 1; ++i) {
        if (diff[i] < 0) {
            if (left != -1 && right != i) {
                std::cout << -1;
                return;
            }

            is_good = false;
            if (left == -1) {
                left = left_zero == -1 ? i : left_zero;
            }
            right = i + 1;
        }

        else if (diff[i] == 0) {
            if (left_zero == -1) left_zero = i;
            if (right == i) right = i + 1;
        }

        else {
            left_zero = -1;
        }
    }

    if (is_good) {
        std::cout << 0;
        return;
    }
    if (left > 0 && right < n - 1) {
        if (a[left - 1] <= a[right] && a[left] <= a[right + 1]) {
            std::cout << left + 1 << ' ' << right + 1;
            return;
        } else {
            std::cout << -1;
            return;
        }
    }

    if (left != 0) {
        if (a[left - 1] <= a[right]) {
            std::cout << left + 1 << ' ' << right + 1;
            return;
        } else {
            std::cout << -1;
            return;
        }
    }

    if (right != n - 1) {
        if (a[left] <= a[right + 1]) {
            std::cout << left + 1 << ' ' << right + 1;
            return;
        } else {
            std::cout << -1;
            return;
        }
    }

    std::cout << left + 1 << ' ' << right + 1;
}

signed main() {
    int t = 1;
    while (t--) {
        solve();
    }
}