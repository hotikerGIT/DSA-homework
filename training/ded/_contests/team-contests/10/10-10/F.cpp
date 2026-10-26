#include <iostream>
#include <vector>
#include <functional>
#include <set>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<char>> matrix(n, std::vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    std::set<std::pair<int, int>> component;
    std::function<void(int, int)> dfs = [&](int i, int j) {
        if (component.contains({i, j})) return;
        if (i < 0 || j < 0 || i >= n || j >= m) return;
        if (matrix[i][j] == '.' || matrix[i][j] == '#') return;
        if (matrix[i][j] == 'C') component.emplace(i, j);

        dfs(i + 1, j);
        dfs(i, j + 1);
        dfs(i - 1, j);
        dfs(i, j - 1);
    };

    auto valid = [&](int i, int j) {
        if (matrix[i][j + 1] == '.' ||
            matrix[i][j - 1] == '.' ||
            matrix[i - 1][j] == '.' ||
            matrix[i + 1][j] == '.') return false;
        return true;
    };

    auto check = [&]() {
        for (auto& p : component) {
            if (!valid(p.first, p.second)) return false;
        }
        return true;
    };

    for (int i = 0; i < n; ++i) {
        if (matrix[i][0] == 'C') matrix[i][0] = '.';
        if (matrix[i][m - 1] == 'C') matrix[i][m - 1] = '.';
    }

    for (int j = 0; j < n; ++j) {
        if (matrix[0][j] == 'C') matrix[0][j] = '.';
        if (matrix[n - 1][j] == 'C') matrix[n - 1][j] = '.';
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 'C') {
                component.clear();
                dfs(i, j);

                if (check()) {
                    res++;

                    for (auto& [ab, abc] : component) {
                        matrix[ab][abc] = '.';
                    }
                } else {
                    for (auto& [ab, abc] : component) {
                        matrix[ab][abc] = '.';
                    }
                }
            }
        }
    }

    std::cout << res;
}