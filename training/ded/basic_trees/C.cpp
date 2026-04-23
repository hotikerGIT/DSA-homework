#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<int> sizes;
std::vector<int> depths;

void dfs(int cur, int prev) {
    sizes[cur] = 1;

    for (int next : graph[cur]) {
        if (next == prev) continue;
        depths[next] = depths[cur] + 1;
        dfs(next, cur);
        sizes[cur] += sizes[next];
    }
}

int k, v = 0, v_prev = -1;
void dfs_pick(int cur, int prev) {
    if (sizes[cur] < k) return;
    if (v == 0 || depths[cur] > depths[v]) {
        v_prev = prev;
        v = cur;
    }

    for (int next : graph[cur]) {
        if (next == prev) continue;
        dfs_pick(next, cur);
    }
}

std::vector<int> choice;
void dfs_choice(int cur, int prev) {
    if ((int)choice.size() == k) return;
    choice.push_back(cur);

    for (int next : graph[cur]) {
        if (next == prev) continue;
        dfs_choice(next, cur);
    }
}

int main() {
    int n;
    std::cin >> n >> k;
    graph.resize(n + 1);
    sizes.resize(n + 1);
    depths.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a;
        std::cin >> a;
        graph[a].push_back(i + 2);
        graph[i + 2].push_back(a);
    }
    dfs(1, -1);
    dfs_pick(1, -1);

    if (v == 0) {
        std::cout << -1;
        return 0;
    }

    dfs_choice(v, v_prev);
    for (int num : choice) {
        std::cout << num << ' ';
    }
    return 0;
}