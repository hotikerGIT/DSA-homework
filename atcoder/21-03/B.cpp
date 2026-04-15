#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::unordered_map<int, int>> c(n - 1);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; ++j) {
            int tmp;
            std::cin >> tmp;
            c[i][j] = tmp;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (c[i][k] > c[i][j] + c[j][k]) {
                    std::cout << "Yes";
                    return 0;
                }
            }
        }
    }

    std::cout << "No";
}