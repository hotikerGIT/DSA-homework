#include <iostream>
#include <vector>
#include <deque>
#include <functional>

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

    std::vector<int> visited(n);
    std::deque<int> q;
    for (int i = 0; i < n; ++i) {
        if (dependencies[i]) continue;
        if (types[i] == 1) q.push_back(i);
        else q.push_front(i);
    }

    int ans = 0;
    int last_type = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();

        if (last_type == 0 && types[v] == 1) {
            ans++;
        }

        last_type = types[v];

        for (int next : graph[v]) {
            dependencies[next]--;

            if (dependencies[next] == 0) {
                if (types[next] == 1) q.push_back(next);
                else q.push_front(next);
            }
        }
    }

    std::cout << ans;
}