#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

int main() {
    int n, m, k;
    std::cin >> n >> m;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m, 2000));

    std::queue<std::pair<int, int>> q;
    std::unordered_set<int> visited;
    std::cin >> k;
    while (k--) {
        int x, y;
        std::cin >> x >> y;
        --x;--y;
        matrix[x][y] = 1;
        q.emplace(x, y);
    }

    while (!q.empty()) {
        auto& [x, y] = q.front();
        q.pop();
        int val = x * n + y;

        if (visited.contains(val)) continue;
        visited.insert(val);

        std::vector<std::pair<int, int>> directions = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
        for (auto& [dx, dy] : directions) {
            int xn = x + dx;
            int yn = y + dy;
            if (xn >= 0 && xn < n && yn >= 0 && yn < n && matrix[xn][yn] > matrix[x][y] + 1) {
                matrix[xn][yn] = matrix[x][y] + 1;
                q.emplace(xn, yn);
            }
        }
    }

    int best = 0;
    std::pair<int, int> coords = {-1, -1};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > best) {
                coords = {i + 1, j + 1};
                best = matrix[i][j];
            }
        }
    }

    std::cout << coords.first << ' ' << coords.second;
}