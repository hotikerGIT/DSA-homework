#include <iostream>
#include <vector>
#include <queue>

int main() {
    int h, w;
    std::cin >> h >> w;
    std::vector<std::vector<char>> grid(h, std::vector<char>(w)), ans(h, std::vector<char>(w, '.'));
    std::queue<std::tuple<int, int, int>> q;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            std::cin >> grid[i][j];
        }
    }

    std::vector<std::vector<char>> next(h, std::vector<char>(w, '.'));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (grid[i][j] == '#') {
                continue;
            }

            for (int x = -1; x < 2; ++x) {
                for (int y = -1; y < 2; ++y) {
                    if (x == 0 && y == 0) continue;
                    if (x + j < w && x + j >= 0 && y + i < h && y + i >= 0 && grid[y + i][x + j] == '#') {
                        next[i][j] = '#';
                    }
                }
            }
        }
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (next[i][j] == '#') {
                q.emplace(i, j, 0);
            }
        }
    }

    std::vector<int> visited(h * w + 10);
    while (!q.empty()) {
        auto [i, j, dist] = q.front();
        q.pop();

        if (visited[i * w + j]) continue;
        visited[i * w + j] = true;
        ans[i][j] = dist % 2 != 0 ? '#' : '.';

        for (int x = -1; x < 2; ++x) {
            for (int y = -1; y < 2; ++y) {
                if (x + j < w && x + j >= 0 && y + i < h && y + i >= 0) {
                    q.emplace(y + i, x + j, dist + 1);
                }
            }
        }
    }

    for (auto& row : ans) {
        for (auto chr : row) {
            std::cout << chr;
        }

        std::cout << '\n';
    }

}