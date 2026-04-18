#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::sort(a.begin(), a.end());

    int first_pos = 0;
    while (first_pos < n && a[first_pos] <= 0) first_pos++;

    int neg_count = 0;
    for (int i = 0; i < n; ++i) if (a[i] < 0) neg_count++;

    int pos_count = n - first_pos;

    long long ans = 0;
    for (int i = first_pos; i < n; ++i) ans += a[i];

    if (neg_count > pos_count) {
        int excess = neg_count - pos_count;
        int med_idx = first_pos - excess + (int)std::ceil((excess + 1) / 2.0) - 1;
        ans += a[med_idx];
    }

    std::cout << ans;
    return 0;
}