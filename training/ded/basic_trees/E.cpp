#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
#define int long long

std::vector<std::vector<int>> graph;
std::vector<int> depths, marked_depth, sizes;

void dfs(int cur, int prev) {
    sizes[cur] = 1;

    for (int next : graph[cur]) {
        if (next == prev) continue;
        depths[next] = depths[cur] + 1;
        dfs(next, cur);
        sizes[cur] += sizes[next];
    }
}


void dfs_marked(int cur, int prev, std::set<int>& marked) {
    if (marked.contains(cur)) marked_depth[cur] = marked_depth[prev] + 1;

    for (int next : graph[cur]) {
        if (next == prev) continue;
        dfs_marked(next, cur, marked);
    }
}

signed main() {
    int n, k;
    std::cin >> n >> k;
    graph.resize(n + 1);
    depths.resize(n + 1);
    marked_depth.resize(n + 1, - 1);
    sizes.resize(n + 1, 0);
    std::vector<int> vertices(n);
    std::iota(vertices.begin(), vertices.end(), 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1, 0);
    std::vector<int> score(n + 1);
    for (int v = 1; v <= n; ++v) {
        score[v] = depths[v] - sizes[v] + 1;
    }
    std::sort(vertices.begin(), vertices.end(), [&](int a, int b) { return score[a] > score[b]; });
    std::set<int> marked(vertices.begin(), vertices.begin() + k);
    dfs_marked(1, 0, marked);

    int ans = 0;
    for (int v = 1; v <= n; ++v) {
        if (marked_depth[v] == -1) continue;
        ans += depths[v] - marked_depth[v];
    }

    std::cout << ans;
}