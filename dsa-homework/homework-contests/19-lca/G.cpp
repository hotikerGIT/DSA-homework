#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

std::vector<int> merge_to_fit(const std::vector<int>& s1, const std::vector<int>& s2) {
    std::vector<int> merged;
    merged.reserve(10);

    auto it1 = s1.begin();
    auto it2 = s2.begin();

    while (merged.size() < 10 && (it1 != s1.end() || it2 != s2.end())) {
        if (it2 == s2.end()) {
            merged.push_back(*it1++);
        } else if (it1 == s1.end()) {
            merged.push_back(*it2++);
        } else if (*it1 < *it2) {
            merged.push_back(*it1++);
        } else if (*it2 < *it1) {
            merged.push_back(*it2++);
        } else {
            merged.push_back(*it1++);
            it2++;
        }
    }

    return merged;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 1; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<int> people(m + 1);
    std::vector<std::vector<int>> people_map(n + 1);
    for (int i = 1; i <= m; ++i) {
        std::cin >> people[i];

        if (people_map[people[i]].size() < 10) people_map[people[i]].push_back(i);
    }

    int log = std::log2(n) + 1;
    std::vector up_pred(n + 1, std::vector<int>(log, 1));
    std::vector up_min(n + 1, std::vector(log, std::vector<int>()));
    std::vector<int> depth(n + 1);

    std::function<void(int, int)> dfs_bin_up = [&](int cur, int prev) {
        depth[cur] = depth[prev] + 1;

        up_pred[cur][0] = prev;
        up_min[cur][0] = merge_to_fit(people_map[cur], people_map[prev]);

        for (int power = 1; power < log; ++power) {
            int predecessor = up_pred[cur][power - 1];
            up_pred[cur][power] = up_pred[predecessor][power - 1];
            up_min[cur][power] = merge_to_fit(up_min[cur][power - 1], up_min[predecessor][power - 1]);
        }

        for (int next : graph[cur]) {
            if (prev == next) continue;
            dfs_bin_up(next, cur);
        }
    };

    dfs_bin_up(1, 1);

    for (int i = 0; i < q; ++i) {
        int v, u, a;
        std::cin >> v >> u >> a;

        if (depth[v] < depth[u]) std::swap(v, u);
        int diff = depth[v] - depth[u];
        std::vector<int> answer;

        for (int j = log - 1; j >= 0; --j) {
            if (diff & (1 << j)) {
                answer = merge_to_fit(answer, up_min[v][j]);
                v = up_pred[v][j];
            }
        }

        if (v != u) {
            for (int j = log - 1; j >= 0; --j) {
                if (up_pred[v][j] != up_pred[u][j]) {
                    answer = merge_to_fit(answer, up_min[v][j]);
                    answer = merge_to_fit(answer, up_min[u][j]);
                    v = up_pred[v][j];
                    u = up_pred[u][j];
                }
            }

            answer = merge_to_fit(answer, people_map[v]);
            answer = merge_to_fit(answer, people_map[u]);
            v = up_pred[v][0];

        }

        answer = merge_to_fit(answer, people_map[v]);

        int k = std::min(a, (int)answer.size());
        std::cout << k << ' ';
        for (int res = 0; res < k; ++res) {
            std::cout << answer[res] << ' ';
        }
        std::cout << '\n';
    }
}