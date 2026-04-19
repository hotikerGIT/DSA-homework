#include <queue>
#include <iostream>
#include <unordered_set>

int main() {
    int n, m;
    std::cin >> n >> m;
    if (m <= n) {
        std::cout << n - m;
        return 0;
    }

    std::queue<std::pair<int, int>> q;
    q.emplace(n, 0);
    std::unordered_set<int> visited;

    int ans = 1e9;

    while (!q.empty()) {
        auto [num, d] = q.front();
        q.pop();
        if (visited.contains(num)) continue;
        visited.insert(num);

        if (num >= m) {
            ans = std::min(ans, num - m + d);
            continue;
        }

        if (num <= 0) continue;

        q.emplace(num - 1, d + 1);
        q.emplace(num * 2, d + 1);
    }

    std::cout << ans;
}