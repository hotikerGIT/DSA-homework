#include <iostream>
#include <vector>
#define int long long

void solve(const std::vector<int>& square) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& x : a) std::cin >> x;
    std::vector<std::vector<int>> graph(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<int> sizes(n + 1);

    auto comb3 = [&](int num) -> int {
        if (num < 3) return 0;
        return num * (num - 1) * (num - 2) / 6;
    };

    auto comb2 = [&](int num) -> int {
        if (num < 2) return 0;
        return num * (num - 1) / 2;
    };

    int ans = 0;
    auto dfs = [&](auto&& self, int cur, int prev) -> void {
        int sub_cnt = 1;

        int sum_not = comb3(n - 1);
        int sum_in = comb2(n - 1);

        for (int next : graph[cur]) {
            if (next != prev) {
                self(self, next, cur);

                sum_in -= comb2(sizes[next]);
                sum_not -= comb3(sizes[next]) + comb2(sizes[next]) * (n - 1 - sizes[next]);

                sub_cnt += sizes[next];
            }
        }

        sum_in -= comb2(n - sub_cnt);
        sum_not -= comb3(n - sub_cnt) + comb2(n - sub_cnt) * (sub_cnt - 1);

        if (square[a[cur - 1]]) {
            if (graph[cur].size() >= 2) ans += sum_in;
            if (graph[cur].size() >= 3) ans += sum_not;
        }

        sizes[cur] = sub_cnt;
    };
    dfs(dfs, 1, 0);

    std::cout << ans << std::endl;
}

signed main() {
    std::vector<int> square(1e6 + 1);
    for (int i = 1; i * i <= (int)1e6; ++i) {
        square[i * i] = 1;
    }

    int t;
    std::cin >> t;
    while (t--) solve(square);
}