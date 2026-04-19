#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> forward(n), backward(n);
    for (int i = 0; i < n; ++i) std::cin >> forward[i];
    for (int i = 0; i < n; ++i) std::cin >> backward[i];

    if (forward[0] == 0) {
        std::cout << "NO";
        return 0;
    }

    if (forward[m - 1] == 1) {
        std::cout << "YES";
        return 0;
    }

    if (backward[m - 1] == 0) {
        std::cout << "NO";
        return 0;
    }

    for (int i = m; i < n; ++i) {
        if (forward[i] && backward[i]) {
            std::cout << "YES";
            return 0;
        }
    }

    std::cout << "NO";
    return 0;
}