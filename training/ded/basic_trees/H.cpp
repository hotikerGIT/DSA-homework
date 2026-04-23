#include <iostream>
#include <vector>
#include <queue>
#define int long long

std::vector<int> parents;
std::vector<int> degree;
std::vector<std::vector<int>> graph;

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    parents.resize(n + 1, 0);
    degree.resize(n + 1, 0);
    graph.resize(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
        degree[a]++;
        degree[b]++;
    }

    std::vector<int> marking(n + 1, -1);
    int unmarked = n;
    std::queue<int> q;

    for (int v = 1; v <= n; ++v) {
        if (degree[v] <= 1) {
            q.push(v);
        }
    }

    while (unmarked > 0) {
        std::queue<int> parents_queue;

        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (marking[v] != -1) continue;

            marking[v] = 0;
            unmarked--;

            for (int u : graph[v]) {
                if (marking[u] == -1) {
                    degree[u]--;

                    if (marking[v] == 0) {
                        marking[u] = 1;
                        unmarked--;
                        parents_queue.push(u);
                    }
                }
            }
        }

        while (!parents_queue.empty()) {
            int v = parents_queue.front(); parents_queue.pop();

            for (int u : graph[v]) {
                if (marking[u] == -1) {
                    marking[u] = 0;
                    unmarked--;
                    degree[u] = 0;

                    for (int w : graph[u]) {
                        if (marking[w] == -1) {
                            degree[w]--;
                            if (degree[w] <= 1) q.push(w);
                        }
                    }
                }
            }
        }

        if (q.empty() && unmarked > 0) {
            for (int v = 1; v <= n; ++v) {
                if (marking[v] == -1 && degree[v] <= 1) q.push(v);
            }
        }
    }

    for (int v = 1; v <= n; ++v) {
        std::cout << marking[v] << ' ';
    }
    std::cout << '\n';
}