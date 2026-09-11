#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define int long long

struct edge {
    int from, to, w;
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int from, to, w;
        std::cin >> from >> to >> w;
        graph[from].emplace_back(from, to, w);
        graph[to].emplace_back(to, from, w);
    }

    std::vector<int> dist(n + 1, 1e18), prev(n + 1);
    dist[1] = 0;
    prev[0] = -1;
    prev[1] = -1;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> heap;
    heap.emplace(0, 1);
    while (!heap.empty()) {
        auto [cur_dist, v] = heap.top();
        heap.pop();

        if (cur_dist > dist[v]) continue;
        for (auto& [from, to, w] : graph[v]) {
            int new_dist = dist[v] + w;

            if (new_dist < dist[to]) {
                dist[to] = new_dist;
                heap.emplace(new_dist, to);
                prev[to] = v;
            }
        }
    }

    if (dist[n] == 1e18) {
        std::cout << -1;
        return 0;
    }

    int cur = n;
    std::vector<int> res;
    while (cur != -1) {
        res.push_back(cur);
        cur = prev[cur];
    }
    std::reverse(res.begin(), res.end());

    for (int num : res) std::cout << num << ' ';
}