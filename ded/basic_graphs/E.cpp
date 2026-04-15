#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::unordered_map<int, std::vector<int>> graph;

    while (true) {
        int x, y;
        std::cin >> x;
        if (x == 0) break;
        std::cin >> y;
        graph[x].push_back(y);
    }

    std::unordered_set<int> visited;
    std::queue<int> q;
    q.push(k);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (visited.contains(node)) continue;
        visited.insert(node);

        for (int next : graph[node]) {
            q.push(next);
        }
    }

    std::cout << (visited.size() == n ? "Yes" : "No");
    return 0;
}