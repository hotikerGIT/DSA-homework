#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>


int main() {
    int n, cnt = 0;
    std::cin >> n;
    std::unordered_map<int, std::vector<int>> graph;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int connect;
            std::cin >> connect;
            if (connect) {
                graph[i].push_back(j);
                cnt++;
            }
        }
    }

    if (cnt / 2 != n - 1) {
        std::cout << "NO";
        return 0;
    }

    std::unordered_set<int> visited;
    std::queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (visited.contains(node)) continue;
        visited.insert(node);

        for (int next : graph[node]) {
            q.push(next);
        }
    }

    std::cout << (visited.size() == n ? "YES" : "NO");

    return 0;
}