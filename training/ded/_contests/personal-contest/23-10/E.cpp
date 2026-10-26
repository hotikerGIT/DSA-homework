#include <iostream>
#include <vector>
#include <queue>

int main() {

    int n, m, p;
    std::cin >> n >> m >> p;
    std::vector matrix(n, std::vector<char>(m));
    for (auto& row : matrix) for (auto& x : row) std::cin >> x;

    std::vector<std::vector<int>> check(n, std::vector<int>(m, 1));
    for (int i = 0; i < n; ++i) {
        int bad_cnt = 0;
        int left = 0;
        int right = p;

        while (right != m) {
            bad_cnt += matrix[i][right] == 'X';
            bad_cnt -= matrix[i][left] == 'X';

            ++left;
            ++right;

            if (bad_cnt) check[i][right - 1] = 0;
        }
    }

    for (int j = 0; j < m; ++j) {
        int bad_cnt = 0;
        int left = 0;
        int right = p;

        while (right != n) {
            bad_cnt += matrix[right][j] == 'X';
            bad_cnt -= matrix[left][j] == 'X';

            ++left;
            ++right;

            if (bad_cnt) check[right - 1][j] = 0;
        }
    }

    std::vector best(n, std::vector<int>(m, -1));
    std::queue<std::vector<int>> q;
    q.push({p - 1, p - 1, 0});

    while (!q.empty()) {
        auto r = q.front();
        q.pop();
        int y = r[0];
        int x = r[1];
        int dist = r[2];

        if (best[y][x] != -1) continue;
        best[y][x] = dist;

        if (y + 1 < n) {
            if (check[y + 1][x]) {
                q.push({y + 1, x, dist + 1});
            }
        }

        if (y >= p) {
            if (check[y - 1][x]) {
                q.push({y - 1, x, dist + 1});
            }
        }

        if (x + 1 < m) {
            if (check[y][x + 1]) {
                q.push({y, x + 1, dist + 1});
            }
        }

        if (x >= p) {
            if (check[y][x - 1]) {
                q.push({y, x - 1, dist + 1});
            }
        }
    }

    std::cout << best.back().back();
}