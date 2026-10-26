#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

int main() {
    long long n;
    int m;
    std::cin >> n >> m;
    std::vector<int> jumps(m);
    for (int i = 0; i < m; ++i) std::cin >> jumps[i];

    std::queue<std::pair<long long, long long>> q;
    q.emplace(n, 0ll);

    std::unordered_set<long long> visited;

    while (!q.empty()) {
        auto& [num, moves] = q.front();
        q.pop();

        if (num == 1) {
            std::cout << moves;
            return 0;
        }

        if (visited.contains(num)) continue;
        visited.insert(num);

        for (auto jump : jumps) {
            if (num % jump != 0) continue;
            q.emplace(num / jump - 1, moves + 1);
        }
    }

    std::cout << -1;
}