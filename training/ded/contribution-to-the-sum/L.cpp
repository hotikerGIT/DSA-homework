#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& x : a) std::cin >> x;
    std::vector<std::vector<int>> graph(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<int> square(1e6 + 1);
    for (int i = 1; i * i <= 1e6; ++i) {
        square[i] = 1;
    }


}

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}