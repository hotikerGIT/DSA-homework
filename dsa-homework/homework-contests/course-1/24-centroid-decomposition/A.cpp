#include <iostream>
#include <vector>
#include <functional>
#define int long long

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<int> removed(n + 1), sizes(n + 1);
    int ans = 0;

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

    std::function<void(int, int, int, std::vector<int>&)> fill_counter = [&](int cur, int prev, int cur_dist, std::vector<int>& to_fill) {
        to_fill[cur_dist]++;

        for (int next : graph[cur]) {
            if (!removed[next] && next != prev && cur_dist + 1 <= k) {
                fill_counter(next, cur, cur_dist + 1, to_fill);
            }
        }
    };

    std::function<void(int)> decompose = [&](int start) {
        dfs_sizes(start, -1);
        int c = find_centroid(start, -1, sizes[start]);

        std::vector<int> total_counter(k + 1);
        total_counter[0] = 1;

        for (int next : graph[c]) {
            if (!removed[next]) {
                std::vector<int> component_counter(k + 1);
                fill_counter(next, c, 1, component_counter);

                for (int i = 0; i <= k; ++i) {
                    ans += component_counter[i] * total_counter[k - i];
                }

                for (int i = 0; i <= k; ++i) {
                    total_counter[i] += component_counter[i];
                }
            }
        }

        removed[c] = true;
        for (int next : graph[c]) {
            if (!removed[next]) {
                decompose(next);
            }
        }
    };

    decompose(1);
    std::cout << ans << '\n';
}