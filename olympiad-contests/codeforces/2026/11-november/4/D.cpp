#include <iostream>
#include <vector>
#include <set>

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    if (n % 2 == 0) {
        std::cout << n + 1 << '\n';
        return;
    }

    auto contains_free = [&](std::set<int> container, int target) {
        while (!container.empty()) {
            int first = *container.begin();

            if (container.contains(target - first)) {
                container.erase(first);
                container.erase(target - first);
            } else {
                break;
            }
        }

        return !container.empty();
    };

    auto determine = [&](int interest, int k) {
        std::vector<std::set<int>> trees(graph[interest].size());

        auto dfs = [&](int cur, int prev, int id, auto&& self) -> void {
            trees[id].insert(cur);

            for (int next : graph[cur]) {
                if (next != prev) self(next, cur, id, self);
            }
        };

        for (int i = 0; i < graph[interest].size(); ++i) {
            int sub = graph[interest][i];
            dfs(sub, interest, i, dfs);
        }

        int free_cnt = 0;
        for (auto& st : trees) free_cnt += contains_free(st, k);

        return free_cnt > 1;
    };

    if (determine(1, n + 2)) {
        std::cout << n + 2 << '\n';
        return;
    }

    if (determine(n, n)) {
        std::cout << n << '\n';
        return;
    }

    std::cout << n + 1 << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) solve();
}