#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> parent(n + 1);
    parent[1] = 1;
    for (int i = 2; i <= n; ++i) std::cin >> parent[i];

    std::vector<std::vector<int>> ancestors(n + 1);
    for (int i = 1; i <= n; ++i) {
        int v = i;

        while (parent[v] != v) {
            ancestors[i].push_back(v);
            v = parent[v];
        }
        ancestors[i].push_back(v);
    }

    for (int i = 0; i < q; ++i) {
        int a, b;
        std::cin >> a >> b;
        std::cout << ancestors[a][b] << '\n';
    }
}