#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int p;
        std::cin >> p;
        graph[p].push_back(i + 2);
        graph[i + 2].push_back(p);
    }

    int res = 0;
    auto dfs = [&](this auto&& self, int cur, int prev) -> int {
        int sub_cnt = 1;

        for (int next : graph[cur]) {
            if (next != prev) {
                sub_cnt += self(next, cur);
            }
        }

        res += sub_cnt * (n - sub_cnt);

        return sub_cnt;
    };

    dfs(1, 0);
    std::cout << res;
}