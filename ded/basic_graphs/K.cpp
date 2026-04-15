#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

struct Cell {
    int row;
    int col;
    int moves;
    char type;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<char>> matrix(n, std::vector<char>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int x1, x2, y1, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    --x1; --x2; --y1; --y2;

    std::unordered_set<int> visited;
    std::queue<Cell> q;
    q.emplace(x1, y1, 0, matrix[x1][y1]);

    while (!q.empty()) {
        Cell c = q.front();
        int val = c.row * n + c.col;
        q.pop();

        if (c.row == x2 && c.col == y2) {
            std::cout << c.moves;
            return 0;
        }

        if (visited.contains(val) || c.type == 'x') continue;
        visited.insert(val);

        std::vector<std::pair<int, int>> directions;
        if (c.type == 'p') directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        else directions = {{2, 1}, {2, -1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}};

        for (auto& [i, j] : directions) {
            int x = c.row + i;
            int y = c.col + j;

            if (x >= 0 && x < n && y >= 0 && y < n) q.emplace(x, y, c.moves + 1, matrix[x][y]);
        }
    }

    std::cout << -1;
}