#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<int, vector<int>> graph;
vector<bool> visited;
int ans;

int dfs(int u, int parent) {
    visited[u] = true;

    vector<int> child_lengths;

    for (int v : graph[u]) {
        if (v == parent) continue;

        if (graph[v].size() >= 3) {
            int len = dfs(v, u);
            child_lengths.push_back(len);
        } else {
            dfs(v, u);
        }
    }

    if (child_lengths.empty()) {
        return 1;
    }

    sort(child_lengths.begin(), child_lengths.end(), greater<int>());

    if (child_lengths.size() >= 2) {
        if (graph[u].size() >= 4) {
            ans = max(ans, child_lengths[0] + child_lengths[1] + 1);
        }
    }

    if (parent == -1) {
        if (graph[u].size() >= 3) {
            ans = max(ans, child_lengths[0] + 1);
            return child_lengths[0] + 1;
        }
    } else {
        if (graph[u].size() >= 4) {
            ans = max(ans, child_lengths[0] + 1);
            return child_lengths[0] + 1;
        }
    }

    return 1;
}

int solve(int n) {
    graph.clear();
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    ans = 0;
    visited.assign(n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && graph[i].size() >= 3) {
            dfs(i, -1);
        }
    }

    if (ans == 0) {
        for (int i = 1; i <= n; i++) {
            if (graph[i].size() >= 3) {
                ans = 1;
                break;
            }
        }
    }

    return ans;
}

int main() {
    int q;
    cin >> q;

    while (q--) {
        int n;
        cin >> n;
        cout << solve(n) << '\n';
    }

    return 0;
}