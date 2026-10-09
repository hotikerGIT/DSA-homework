#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
signed main() {
    int n;
    std::cin >> n;
    int max_index = 0;
    std::vector<std::pair<int, int>> intervals(n), copy(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> intervals[i].first;
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> intervals[i].second;
        if (intervals[max_index].second < intervals[i].second) max_index = i;
    }

    int second_index = !max_index;
    for (int i = 0; i < n; ++i) {
        if (i == max_index) continue;
        if (intervals[second_index].second < intervals[i].second) second_index = i;
    }

    if (n == 1) {
        if (intervals[0].first == 0) {
            std::cout << 0;
        } else {
            std::cout << -1;
        }

        return 0;
    }

    std::vector<int> ans(n);
    int check_sum = 0;
    for (int i = 0; i < n; ++i) {
        if (i != max_index) {
            check_sum += intervals[i].second;
            ans[i] = intervals[i].second;
        }
    }

    ans[max_index] = std::max(intervals[second_index].second, intervals[max_index].first);

    if (check_sum < ans[max_index]) {
        std::cout << -1;
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
}