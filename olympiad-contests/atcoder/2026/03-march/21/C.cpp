#include <iostream>
#include <vector>

// выходит ли фигура за границы?
bool dfs(std::vector<std::vector<char>>& matrix, bool flag, int i, int j) {
    if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size()) {
        return true;
    }

    if (matrix[i][j] == '#') return false;

    if (matrix[i][j] == '.') {
        matrix[i][j] = '#';
    }

    std::vector<std::pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    bool ans = false;
    for (auto d : dirs) {
        ans |= dfs(matrix, flag, i + d.first, j + d.second);
    }

    return ans;
}

int main() {
    int h, w;
    std::cin >> h >> w;
    std::vector<std::vector<char>> board(h, std::vector<char>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            std::cin >> board[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (board[i][j] == '.') {
                ans += !dfs(board, false, i, j);
            }
        }
    }

    std::cout << ans;
}