#include <iostream>
#include <vector>

int dfs(std::vector<std::vector<int>>& graph, int current, std::vector<int>& dp, std::vector<int>& path) {
    int res = 1;
    path[current] = 1;

    for (int num : graph[current]) {
        if (path[num] == 1) continue;

        if (dp[num] != 0) {
            res = std::max(dp[num] + 1, res);
            continue;
        }

        path[num] = 1;
        res = std::max(dfs(graph, num, dp, path) + 1, res);
        path[num] = 0;
    }

    path[current] = 0;
    dp[current] = res;
    return res;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> perm(k, std::vector<int>(n));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            int tmp;
            std::cin >> tmp;
            perm[i][tmp - 1] = j;
        }
    }

    int ans = 1;
    std::vector<int> dp(n, 0);
    std::vector<std::vector<int>> graph(n);
    std::vector<int> path(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool flag = true;

            for (int a = 0; a < k; ++a) {
                if (perm[a][i] < perm[a][j]) {
                    flag = false;
                    break;
                }
            }

            if (flag) {
                graph[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        dfs(graph, i, dp, path);
        ans = std::max(dp[i], ans);
    }

    std::cout << ans;
}