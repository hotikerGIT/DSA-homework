#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

std::multiset<int> present;
std::vector<bool> answer;
std::vector<int> a;
std::unordered_map<int, std::vector<int>> graph;

void dfs(int current, int parent, bool flag) {
    if (flag || present.contains(a[current])) {
        answer[current] = true;
        flag = true;
    }

    present.insert(a[current]);

    for (auto child : graph[current]) {
        if (child == parent) continue;
        dfs(child, current, flag);
    }

    present.erase(present.find(a[current]));
}

int main() {
    int n;
    std::cin >> n;
    answer.resize(n);
    a.resize(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(0, -1, false);

    for (bool flag : answer) {
        std::cout << (flag ? "Yes" : "No") << '\n';
    }
}