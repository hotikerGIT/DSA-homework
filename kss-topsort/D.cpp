#include <iostream>
#include <vector>
#include <deque>
#include <queue>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> types(n);
    std::vector<int> dependencies(n);

    for (int i = 0; i < n; ++i) std::cin >> types[i];

    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[b].push_back(a);
        dependencies[a]++;
    }

    std::queue<int> q_main, q_co;
    std::vector<std::queue<int>*> q_types = {&q_main, &q_co};
    for (int v = 0; v < n; ++v) {
        if (dependencies[v]) continue;
        if (types[v] == 0) q_main.push(v);
        else q_co.push(v);
    }

    int ans = 0;
    while (!q_main.empty() || !q_co.empty()) {
        while (!q_main.empty()) {
            int v = q_main.front();
            q_main.pop();

            for (int next : graph[v]) {
                dependencies[next]--;
                if (!dependencies[next]) q_types[types[next]]->push(next);
            }
        }

        if (q_co.empty()) break;
        ans++;

        while (!q_co.empty()) {
            int v = q_co.front();
            q_co.pop();

            for (int next : graph[v]) {
                dependencies[next]--;
                if (!dependencies[next]) q_types[types[next]]->push(next);
            }
        }
    }

    std::cout << ans << '\n';
}