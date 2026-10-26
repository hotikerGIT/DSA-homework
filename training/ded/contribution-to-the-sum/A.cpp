#include <iostream>
#include <vector>
#define int long long

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto& x : a) std::cin >> x;

    int sum_max = 0;
    int sum_min = 0;

    std::vector<std::pair<int, int>> stack_max, stack_min;
    stack_max.reserve(n);
    stack_min.reserve(n);

    int min_stack_sum = 0;
    int max_stack_sum = 0;

    for (int i = 0; i < n; ++i) {
        int cur_left_min = i;
        int cur_left_max = i;

        while (!stack_min.empty() && a[stack_min.back().second] >= a[i]) {
            auto [left, right] = stack_min.back();
            stack_min.pop_back();
            cur_left_min = left;

            min_stack_sum -= (right - left + 1) * a[right];
        }

        while (!stack_max.empty() && a[stack_max.back().second] <= a[i]) {
            auto [left, right] = stack_max.back();
            stack_max.pop_back();
            cur_left_max = left;

            max_stack_sum -= (right - left + 1) * a[right];
        }

        stack_min.emplace_back(cur_left_min, i);
        stack_max.emplace_back(cur_left_max, i);

        min_stack_sum += (i - cur_left_min + 1) * a[i];
        max_stack_sum += (i - cur_left_max + 1) * a[i];

        sum_min += min_stack_sum;
        sum_max += max_stack_sum;
    }

    std::cout << sum_max - sum_min;
}