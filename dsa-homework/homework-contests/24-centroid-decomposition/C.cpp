#include <iostream>
#include <vector>
#include <functional>
#include <map>
#define int long long

struct Centroid {
    int id = 0;
    std::map<int, int> distance;
    int min_red_distance = 2e9;
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<int> removed(n + 1), sizes(n + 1);
    std::vector<std::vector<int>> centroids(n + 1);
    std::vector<Centroid> centroid_data(n + 1);

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

    std::function<void(int, int, int, Centroid&)> find_centroid_data = [&](int cur, int prev, int cur_dist, Centroid& centroid) {
        centroid.distance[cur] = cur_dist;
        centroids[cur].push_back(centroid.id);

        if (cur == 1) {
            centroid.min_red_distance = centroid.distance[cur];
        }

        for (int next : graph[cur]) {
            if (!removed[next] && next != prev) {
                find_centroid_data(next, cur, cur_dist + 1, centroid);
            }
        }
    };

    std::function<void(int)> decompose = [&](int start) {
        dfs_sizes(start, -1);
        int c = find_centroid(start, -1, sizes[start]);
        centroid_data[c].id = c;
        find_centroid_data(c, -1, 0, centroid_data[c]);

        removed[c] = true;
        for (int next : graph[c]) {
            if (!removed[next]) {
                decompose(next);
            }
        }
    };

    decompose(1);

    for (int i = 0; i < m; ++i) {
        int type, v;
        std::cin >> type >> v;

        if (type == 1) {
            for (int cid : centroids[v]) {
                auto& centroid = centroid_data[cid];
                centroid.min_red_distance = std::min(centroid.min_red_distance, centroid.distance[v]);
            }
        } else {
            int ans = 2e9;

            for (int cid : centroids[v]) {
                auto& centroid = centroid_data[cid];
                ans = std::min(ans, centroid.min_red_distance + centroid.distance[v]);
            }

            std::cout << ans << '\n';
        }
    }
}