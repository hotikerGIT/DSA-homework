#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> p(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        x = std::abs(x);
        y = std::abs(y);
        p[i] = {x, y};
    }

    std::sort(p.begin(), p.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });

    std::vector<std::pair<int, int>> points;
    for (auto& pair : p) {
        if (!points.empty() && points.back().first == pair.first) continue;
        while (points.size() >= 2 &&
               (points.back().second - points[points.size()-2].second) * (pair.first - points.back().first) <=
               (pair.second - points.back().second) * (points.back().first - points[points.size()-2].first)) {
            points.pop_back();
               }
        points.push_back(pair);
    }

    std::vector<int> dp(n);
    dp[0] = points[0].first * points[0].second;

    for (int i = 1; i < n; ++i) {
        dp[i] = dp[i - 1] + points[i].first * points[i].second;

        for (int j = 0; j < i; ++j) {
            dp[i] = std::min(dp[i], dp[j] + (points[i].first - points[j].first) * points[j].second);
        }
    }

    std::cout << dp[n - 1] * 4;
}