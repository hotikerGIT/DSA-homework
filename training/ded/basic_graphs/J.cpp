#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

struct Cell {
    int node;
    std::vector<int> trajectory;
    int moves;
};

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, std::vector<int>> graph;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            char connect;
            std::cin >> connect;
            if (connect == '1') graph[i].push_back(j);
        }
    }

    int a, b;
    std::cin >> a >> b;

    std::unordered_set<int> visited;
    std::queue<Cell> q;
    Cell c = Cell(a, {}, 0);
    q.push(c);

    while (!q.empty()) {
        c = q.front();
        q.pop();
        c.trajectory.push_back(c.node);

        if (c.node == b) {
            std::cout << c.moves << '\n';

            for (int num : c.trajectory) {
                std::cout << num << ' ';
            }
            return 0;
        }

        if (visited.contains(c.node)) continue;
        visited.insert(c.node);

        for (int next : graph[c.node]) {
            Cell next_cell = Cell(next, c.trajectory, c.moves + 1);
            q.push(next_cell);
        }
    }

    std::cout << -1;
}