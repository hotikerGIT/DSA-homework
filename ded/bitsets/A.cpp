#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> input(n);
    std::unordered_set<int> can_remove;

    for (int i = 0; i < n; ++i) {
        std::cin >> input[i];
        can_remove.insert(i);
    }

    for (int i = 0; i < m; ++i) {
        int first_index = -1;
        bool removable = true;

        for (int j = 0; j < n; ++j) {
            if (input[j][i] == '1') {
                if (first_index == -1) {
                    first_index = j;
                }

                else {
                    removable = false;
                    break;
                }
            }
        }

        if (removable) {
            can_remove.erase(first_index);
        }
    }

    std::cout << (!can_remove.empty() ? "YES" : "NO");
}