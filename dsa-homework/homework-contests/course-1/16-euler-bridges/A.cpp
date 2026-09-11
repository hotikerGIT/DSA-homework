#include <iostream>
#include <vector>
#include <string>
#include  <algorithm>
std::vector<std::vector<int>> graph;
std::vector<int> height;

void dfs(int cur, int prev, int cnt = 1) {
    height[cur] = std::max(cnt, height[cur]);

    bool equal_flag = false;
    for (int v : graph[cur]) {
        if (v == prev) continue;
        equal_flag = std::find(graph[v].begin(), graph[v].end(), cur) != graph[v].end();
        dfs(v, cur,  height[cur] + !equal_flag);
    }

}

int main() {
    int n;
    std::string s;
    std::cin >> n >> s;
    graph.resize(n);
    height.resize(n, -1);
    for (int i = 1; i <= s.size(); ++i) {
        char c = s[i - 1];

        if (c == '=') {
            graph[i].push_back(i - 1);
            graph[i - 1].push_back(i);
        } else if (c == 'L') {
            graph[i].push_back(i - 1);
        } else if (c == 'R') {
            graph[i - 1].push_back(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (height[i] == -1) dfs(i, -1);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << height[i] << ' ';
    }
}