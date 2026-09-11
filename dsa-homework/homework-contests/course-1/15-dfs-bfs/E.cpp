#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    std::vector<int> pos(n + 1, -1);
    std::vector<bool> visited(n + 1, false);
    std::vector<int> path;

    for (int start = 1; start <= n; start++) {
        if (visited[start]) continue;

        path.clear();
        int cur = start;

        while (true) {
            visited[cur] = true;
            pos[cur] = (int)path.size();
            path.push_back(cur);

            int next = -1;
            for (int nb : graph[cur]) {
                if (!visited[nb]) {
                    next = nb;
                    break;
                }
            }

            if (next == -1) {
                int best_pos = (int)path.size();
                for (int nb : graph[cur]) {
                    if (pos[nb] != -1 && pos[nb] < best_pos) {
                        best_pos = pos[nb];
                    }
                }

                int cycle_len = (int)path.size() - best_pos;
                std::cout << cycle_len << "\n";
                for (int i = best_pos; i < (int)path.size(); i++) {
                    std::cout << path[i];
                    if (i + 1 < (int)path.size()) std::cout << " ";
                }
                std::cout << "\n";
                return 0;
            }

            cur = next;
        }
    }

    return 0;
}