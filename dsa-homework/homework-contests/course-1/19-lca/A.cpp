#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int main() {
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);

    int k;
    std::cin >> k;
    int log = std::log2(k) + 1;
    std::vector<std::vector<int>> up(k + 1, std::vector<int>(log, 1));
    std::vector<int> depth(k + 1);
    depth[1] = 0;

    for (int i = 0; i < k; ++i) {
        std::string type;
        int a, b;
        std::cin >> type >> a >> b;

        if (type == "ADD") {
            up[b][0] = a;

            for (int v = 1; v < log; ++v) {
                up[b][v] = up[up[b][v - 1]][v - 1];
            }

            depth[b] = depth[a] + 1;
        }

        else {
            if (depth[a] < depth[b]) std::swap(a, b);

            int diff = depth[a] - depth[b];
            for (int bit = 0; bit < log; ++bit) {
                if ((diff >> bit) & 1) {
                    a = up[a][bit];
                }
            }
            if (a == b) {
                std::cout << a << '\n';
                continue;
            }

            for (int j = log - 1; j >= 0; --j) {
                if (up[a][j] != up[b][j]) {
                    a = up[a][j];
                    b = up[b][j];
                }
            }

            std::cout << up[a][0] << '\n';
        }
    }
}