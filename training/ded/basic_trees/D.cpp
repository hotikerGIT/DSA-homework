#include <iostream>
#include <vector>
#include <functional>
#define int long long

signed main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<int> order, visited(n + 1), parent(n + 1);
    std::function<void(int)> top_sort = [&](int cur) {
        visited[cur] = 1;
        for (int next : graph[cur]) {
            if (!visited[next]) {
                top_sort(next);
                parent[next] = cur;
            }
        }
        order.push_back(cur);
    };
    top_sort(1);

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1));

    int ans = 0;
    for (int v : order) {
        dp[v][0] = 1;

        for (int u : graph[v]) {
            if (u == parent[v]) continue;

            for (int j = 0; j < k; ++j) {
                dp[v][j + 1] += dp[u][j];
            }
        }
    }

    for (int v = 1; v <= n; ++v) {
        ans += 2 * dp[v][k];

        for (int u : graph[v]) {
            if (u == parent[v]) continue;
            for (int a = 0; a < k - 1; ++a) {
                ans += dp[u][a] * (dp[v][k - a - 1] - dp[u][k - a - 2]);
            }
        }
    }

    std::cout << ans / 2;
}