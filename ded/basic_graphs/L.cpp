#include <iostream>
#include <vector>
#include <queue>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, k;
    std::cin >> n >> m;
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1));
    std::queue<std::pair<int, int>> q;

    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x; --y;
        dist[x][y] = 0;
        q.emplace(x, y);
    }

    // Multi-source BFS
    std::vector<std::pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto& [dx, dy] : directions) {
            int xn = x + dx;
            int yn = y + dy;
            if (xn >= 0 && xn < n && yn >= 0 && yn < m && dist[xn][yn] == -1) {
                dist[xn][yn] = dist[x][y] + 1;
                q.emplace(xn, yn);
            }
        }
    }

    // Найти максимальное расстояние
    int best = -1;
    std::pair<int, int> coords = {1, 1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dist[i][j] > best) {
                best = dist[i][j];
                coords = {i + 1, j + 1};
            }
        }
    }

    std::cout << coords.first << ' ' << coords.second;
    return 0;
}