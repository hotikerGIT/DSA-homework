#include <iostream>
#include <vector>
#include <set>
#include <functional>
#define int long long

signed main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<int> weight(n + 1);
    int root = -1;
    for (int i = 1; i <= n; ++i) {
        int p, m;
        std::cin >> p >> m;

        if (p) {
            graph[p].push_back(i);
            graph[i].push_back(p);
        } else root = i;

        weight[i] = m;
    }

    std::set<int> set;
    int sum = 0;
    int ans = 0;

    auto add_to_set = [&](int w) {
        if (set.contains(k)) return;
        if (set.size() < k) {
            sum += w;
            set.insert(w);

        } else {
            int diff = w - *set.begin();

            if (diff > 0) {
                sum += diff;
                set.insert(w);
                set.erase(set.begin());
            }
        }
    };

    auto remove_from_set = [&](int w) {
        auto it = set.find(w);
        if (it != set.end()) {
            set.erase(it);
            sum -= w;
        }
    };

    std::function<void(int, int)> dfs = [&](int cur, int prev) {
        add_to_set(weight[cur]);

        for (int next : graph[cur])
            if (next != prev) {
                dfs(next, cur);
            }

        ans = std::max(ans, sum);
        remove_from_set(weight[cur]);
    };

    dfs(root, 0);
    std::cout << ans;
}