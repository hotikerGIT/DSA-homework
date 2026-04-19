#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a; --b;

        matrix[a][b] = 1;
        matrix[b][a] = 1;
    }

    int count = 0;
    while (true) {
        std::vector<std::pair<int, int>> ban;

        for (int first = 0; first < n; ++first) {
            int counter = 0;
            std::pair<int, int> p = {-1, -1};

            for (int second = 0; second < n; ++second) {
                if (matrix[first][second]) {
                    counter++;
                    p = {first, second};
                }
            }

            if (counter == 1) {
                ban.push_back(p);
            }
        }

        if (ban.empty()) break;

        for (auto& [a, b] : ban) {
            matrix[a][b] = 0;
            matrix[b][a] = 0;
        }
        count++;
    }

    std::cout << count;
}