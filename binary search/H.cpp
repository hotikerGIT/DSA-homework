#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

int main() {
    int t, n, a;
    std::cin >> t;

    while (t--) {
        std::cin >> n;

        std::vector<int> order(n);
        std::unordered_map<int, std::pair<int, int>> intervals;

        for (int i = 0; i < n; ++i) {
            std::cin >> a;
            order[i] = a;

            if (!intervals.contains(a)) {
                intervals[a].first = i;
            }

            intervals[a].second = i;
        }
        std::sort(order.rbegin(), order.rend());

        int left = 0;
        int right = n - 1;

        std::unordered_set<int> checked;
        for (int num : order) {
            if (checked.contains(num)) { continue; }

            int cur_left = intervals[num].first;
            int cur_right = intervals[num].second;
            int length = cur_right - cur_left + 1;
            int expand = num - length;

            if (cur_left < left || cur_right > right) {
                left = right + 1;
                break;
            }

            left = std::max(left, cur_left - expand);
            right = std::min(right, cur_right + expand);
        }

        std::cout << right - left + 1 << std::endl;
    }
}