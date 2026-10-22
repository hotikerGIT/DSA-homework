#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
    for (auto& row : matrix) for (auto& x : row) std::cin >> x;

    int left = 0;
    int right = 1e9;
    int ans = 1e9;

    auto check = [&](int assume) {
        std::vector<int> visited(n * m);

        auto dfs = [&](int i, int j, auto&& self) {
            if (i < 0 || i >= n ||
                j < 0 || j >= m ||
                visited[i * m + j] ||
                matrix[i][j] > assume) return;

            visited[i * m + j] = true;

            self(i + 1, j, self);
            self(i, j + 1, self);
            self(i, j - 1, self);
        };

        dfs(0, 0, dfs);

        return visited.back();
    };

    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    std::cout << ans;
}