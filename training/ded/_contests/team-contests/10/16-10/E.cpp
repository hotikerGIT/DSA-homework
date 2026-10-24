#include <iostream>
#include <vector>

struct Node {
    int id = -1;
    int cur_xor = 0;
    int unknown = 0;
};

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<Node>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int p;
        std::cin >> p;
        graph[i].push_back(Node(p));
        graph[p].push_back(Node(i));
    }

    int total_xor = 0;
    int total_unknown = 0;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];

        if (a[i] != -1) total_xor ^= a[i];
        else total_unknown++;
    }

    auto dfs = [&](int cur, int prev, auto&& self) {
        for (auto& next : graph[cur]) {
            if (next.id != prev) {
                self(next, cur, self);
            }
        }


    };
}

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}