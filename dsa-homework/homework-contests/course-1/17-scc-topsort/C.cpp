#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> reverse_graph(n + 1);
    std::vector<int> outdegree(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        reverse_graph[b].push_back(a);
        outdegree[a]++;
    }

    std::priority_queue<int> head;

    for (int v = 1; v <= n; ++v) {
        if (outdegree[v] == 0) {
            head.push(v);
        }
    }

    std::vector<int> labels(n + 1);
    int current_label = n;

    while (!head.empty()) {
        int v = head.top();
        head.pop();

        labels[v] = current_label--;

        for (int u : reverse_graph[v]) {
            outdegree[u]--;
            if (outdegree[u] == 0) {
                head.push(u);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << labels[i] << ' ';
    }

    return 0;
}