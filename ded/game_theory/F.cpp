#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<std::vector<int>>>& matrix, const std::vector<std::pair<int, int>>& movement, int i, int j, int k) {
    if (matrix[i][j][k] != -1) return;
    matrix[i][j][k] = 0;

    for (auto vector : movement) {
        int new_i = vector.first + i; int new_j = vector.second + j;
        dfs(matrix, movement, new_i, new_j, k);
        matrix[i][j][k] |= matrix[new_i][new_j][k];

        if (k )
    }
}

int main() {
    const int SIZE = 610;
    const int CENTER = 205;

    int x, y, n, d;
    std::cin >> x >> y >> n >> d;
    std::vector matrix(SIZE, std::vector(SIZE, std::vector<int>(4)));
    std::vector<std::pair<int, int>> movement(n);
    for (int i = 0; i < n; ++i) {
        int xv, yv;
        std::cin >> xv >> yv;
        movement[i] = {xv, yv};
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int distance_squared = (CENTER - i) * (CENTER - i) + (CENTER - j) * (CENTER - j);
            if (distance_squared > d * d) {
                for (int k = 0; k < 4; ++k) matrix[i][j][k] = 1;
            }
        }
    }

    dfs(matrix, movement, CENTER - x, CENTER - y);
    std::cout << (matrix[CENTER - x][CENTER - y] ? "Anton" : "Dasha");
}