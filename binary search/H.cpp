#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

int main() {
    int t, n;
    std::cin >> t;

    while (t--) {
        std::cin >> n;
        int a;
        std::unordered_map<int, std::pair<int, int>> intervals;

        for (int i = 0; i < n; ++i) {
            std::cin >> a;

            if (!intervals.contains(a)) {
                intervals[a].first = i;
            }

            intervals[a].second = i;
        }

        int left = 0;
        int right = n - 1;

        for (aut : intervals) {

        }
    }
}