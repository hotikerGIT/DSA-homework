#include <iostream>
#include <vector>
#include <functional>
#define int long long

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<int> removed(n + 1), sizes(n + 1);
    std::vector<int> ans(n + 1);

    std::function<void(int, int)> dfs_sizes = [&](int cur, int prev) {
        sizes[cur] = 1;

        for (int next : graph[cur]) {
            if (next == prev || removed[next]) continue;
            dfs_sizes(next, cur);

            sizes[cur] += sizes[next];
        }
    };

    std::function<int(int, int, int)> find_centroid = [&](int cur, int prev, int size) {
        for (int next : graph[cur]) {
            if (!removed[next] && next != prev && sizes[next] > size / 2) {
                return find_centroid(next, cur, size);
            }
        }

        return cur;
    };

    std::function<void(int, int)> decompose = [&](int start, int rank) {
        dfs_sizes(start, -1);
        int c = find_centroid(start, -1, sizes[start]);
        ans[c] = rank;

        removed[c] = true;
        for (int next : graph[c]) {
            if (!removed[next]) {
                decompose(next, rank + 1);
            }
        }
    };

    decompose(1, 'A');
    for (int i = 1; i <= n; ++i) {
        std::cout << (char) ans[i] << ' ';
    }
}