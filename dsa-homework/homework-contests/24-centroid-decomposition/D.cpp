#include <iostream>
#include <vector>
#include <functional>
#include <map>
#define int long long

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int ans = 0;
    std::vector<int> vertex_weight(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> vertex_weight[i];
        ans += vertex_weight[i];
    }

    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<int> removed(n + 1), sizes(n + 1);


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

    std::function<void(int, int, int, std::map<int, int>&)> fill_counter = [&](int cur, int prev, int cur_dist, std::map<int, int>& to_fill) {
        cur_dist ^= vertex_weight[cur];
        to_fill[cur] = cur_dist;

        for (int next : graph[cur]) {
            if (!removed[next] && next != prev) {
                fill_counter(next, cur, cur_dist, to_fill);
            }
        }
    };

    std::function<void(int)> decompose = [&](int start) {
        dfs_sizes(start, -1);
        int c = find_centroid(start, -1, sizes[start]);

        std::vector<int> total_count(30);
        int total_size = 1;

        for (int bit = 0; bit < 30; ++bit) {
            total_count[bit] += (vertex_weight[c] >> bit) & 1;
        }

        for (int next : graph[c]) {
            if (!removed[next]) {
                std::map<int, int> component_dist;
                fill_counter(next, c, 0, component_dist);

                for (auto& [vertex, dist] : component_dist) {
                    for (int bit = 0; bit < 30; ++bit) {
                        if ((dist >> bit) & 1) {
                            ans += (total_size - total_count[bit]) * (1 << bit);
                        } else {
                            ans += total_count[bit] * (1 << bit);
                        }
                    }
                }

                for (auto& [vertex, dist] : component_dist) {
                    for (int bit = 0; bit < 30; ++bit) {
                        total_count[bit] += ((dist ^ vertex_weight[c]) >> bit) & 1;
                    }

                    total_size++;
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