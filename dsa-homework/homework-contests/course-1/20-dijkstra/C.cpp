#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n;
    std::cin >> n;
    std::vector dist(n + 1, std::vector<int>(n + 1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> dist[i][j];
        }
    }

    std::vector<int> order(n);
    for (int i = n - 1; i >= 0; --i) std::cin >> order[i];
    std::vector<int> ans(n);


    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int u = order[i], v = order[j], s = order[k];

                dist[u][v] = std::min(dist[u][v], dist[u][s] + dist[s][v]);
            }
        }

        for (int i = 0; i <= k; ++i) {
            for (int j = 0; j <= k; ++j) {
                ans[n - k - 1] += dist[order[i]][order[j]];
            }
        }
    }

    for (int num : ans) std::cout << num << ' ';
}