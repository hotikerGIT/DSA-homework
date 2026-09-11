#include <iostream>
#include <vector>
#include <set>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::set<int> a;
    for (int i = 0; i < k; ++i) {
        int tmp;
        std::cin >> tmp;
        a.insert(tmp - n);
    }

    std::queue<std::pair<int, int>> q;
    q.emplace(0, 0);

    std::vector<int> visited(2001);
    while (!q.empty()) {
        auto& [v, dist] = q.front();
        q.pop();

        if (v == 0 && dist != 0) {
            std::cout << dist;
            return 0;
        }

        int index = v + 1000;
        if (index < 0 || index > 2000 || visited[index]) continue;
        visited[index] = 1;

        for (int next : a) {
            q.emplace(v + next, dist + 1);
        }
    }

    std::cout << -1;
}