#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> ass_graph(n + 1);
    std::vector<std::set<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].insert(b);
        ass_graph[a].push_back(b);
        ass_graph[b].push_back(a);
    }

    int log = std::log2(n) + 1;
    std::vector go_up(n + 1, std::vector<int>(log));
    std::vector get_from(n + 1, std::vector<int>(log));
    std::vector lca(n + 1, std::vector<int>(log));
    std::vector<int> depth(n + 1);

    std::function<void(int, int, bool)> dfs_bin_up = [&](int cur, int prev, bool is_prev_straight) {
        depth[cur] = depth[prev] + 1;

        lca[cur][0] = prev;

        if (is_prev_straight) {
            get_from[cur][0] = true;
        } else {
            go_up[cur][0] = true;
        }

        for (int power = 1; power < log; ++power) {
            int predecessor = lca[cur][power - 1];
            lca[cur][power] = lca[predecessor][power - 1];
            get_from[cur][power] = get_from[cur][power - 1] && get_from[predecessor][power - 1];
            go_up[cur][power] = go_up[cur][power - 1] && go_up[predecessor][power - 1];
        }

        for (int next : ass_graph[cur]) {
            if (next == prev) continue;

            bool flag = false;
            if (graph[cur].contains(next)) {
                flag = true;
            }

            dfs_bin_up(next, cur, flag);
        }
    };

    dfs_bin_up(1, 1, false);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;

        if (x == y) {
            std::cout << "Yes\n";
            continue;
        }

        int difference = std::abs(depth[x] - depth[y]);
        bool cant_reach_from_x = false, cant_reach_to_y = false;

        if (depth[y] > depth[x])  {
            for (int j = log - 1; j >= 0; --j) {
                if (difference & (1 << j)) {
                    cant_reach_to_y |= !get_from[y][j];
                    y = lca[y][j];
                }
            }

        } else if (depth[x] > depth[y]) {
            for (int j = log - 1; j >= 0; --j) {
                if (difference & (1 << j)) {
                    cant_reach_from_x |= !go_up[x][j];
                    x = lca[x][j];
                }
            }
        }

        for (int j = log - 1; j >= 0; --j) {
            if (lca[x][j] != lca[y][j]) {
                cant_reach_from_x |= !go_up[x][j];
                cant_reach_to_y |= !get_from[y][j];
                x = lca[x][j];
                y = lca[y][j];
            }
        }

        if (x != y) {
            cant_reach_from_x |= !go_up[x][0];
            cant_reach_to_y  |= !get_from[y][0];
        }

        std::cout << (cant_reach_to_y || cant_reach_from_x ? "No" : "Yes");
        std::cout << '\n';
    }
}