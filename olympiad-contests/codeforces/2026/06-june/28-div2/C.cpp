#include <iostream>
#include <vector>
#include <map>
#include <functional>

int dfs(std::vector<std::vector<int>>& graph, std::vector<int>& max_down, int cur, int parent) {
    int answer = 1;
    int child_count = 0;

    for (int child : graph[cur]) {
        if (child != parent) {
            child_count++;
            answer += dfs(graph, max_down, child, cur);
        }
    }

    std::map<int, int> freq;
    for (int child : graph[cur]) {
        if (child == parent) continue;
        freq[max_down[child] + 1]++;
    }

    int max_new = 0;
    if (child_count >= 2) {
        auto last_it = std::prev(freq.end());
        if (last_it->second == 1) {
            last_it = std::prev(last_it);
        }
        max_new = last_it->first;
    }

    answer += max_new;
    return answer;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int p;
        std::cin >> p;

        graph[i + 2].push_back(p);
        graph[p].push_back(i + 2);
    }

    std::vector<int> down(n + 1);
    down[0] = -1;

    std::function<void(int, int)> dfs_down = [&](int cur, int prev) {
        int max = -1;

        for (int next : graph[cur]) {
            if (next == prev) continue;
            dfs_down(next, cur);
            max = std::max(max, down[next]);
        }

        down[cur] = max + 1;
    };
    dfs_down(1, 0);

    std::cout << dfs(graph, down, 1, 0) << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}