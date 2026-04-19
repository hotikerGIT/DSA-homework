#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<int>>& grid, int cur_i, int cur_j) {
    if (cur_i < 0 || cur_j < 0 || cur_i == grid.size() || cur_j == grid[0].size() || grid[cur_i][cur_j] == 0) return;
    grid[cur_i][cur_j] = 0;

    dfs(grid, cur_i + 1, cur_j);
    dfs(grid, cur_i - 1, cur_j);
    dfs(grid, cur_i, cur_j + 1);
    dfs(grid, cur_i, cur_j - 1);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector matrix(n, std::vector<int>(m, 0));
    bool no_puzzle_flag = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            std::cin >> c;

            if (c == '*') {
                matrix[i][j] = 1;
                no_puzzle_flag = false;
            }
        }
    }

    if (no_puzzle_flag) {
        std::cout << "NO";
        return 0;
    }

    bool flag1, flag2;
    flag1 = true, flag2 = true;
    for (int i = 0; i < n; ++i) {
        if (matrix[i][0] == 1) flag1 = false;
        if (matrix[i][m - 1] == 1) flag2 = false;
    }

    if (flag1 || flag2) {
        std::cout << "YES";
        return 0;
    }

    flag1 = true; flag2 = true;
    for (int j = 0; j < m; ++j) {
        if (matrix[0][j] == 1) flag1 = false;
        if (matrix[n - 1][j] == 1) flag2 = false;
    }

    if (flag1 || flag2) {
        std::cout << "YES";
        return 0;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 0) continue;
            dfs(matrix, i, j);
            ans++;
        }
    }

    if (ans > 1) std::cout << "YES";
    else std::cout << "NO";
}