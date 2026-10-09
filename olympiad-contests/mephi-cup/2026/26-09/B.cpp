#include <iostream>
#include <vector>
#include <map>

bool debil(const std::vector<int>& a) {
    int check = a[0];

    for (int num : a) if (num != check) return false;
    return true;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    if (debil(a)) {
        std::cout << 0;
        return 0;
    }

    std::map<int, int> best;
    // key - color, value - { best_res, deleted_color, last_index }
    std::map<int, int[3]> running;

    int left_same_index = -1;
    for (int i = 0; i < n; ++i) {
        int color = a[i];
        if (running[color][0] == 0) {
            running[color][0]++;
            running[color][1] = -1;
            running[color][2] = i;
            left_same_index = i;
            continue;
        }

        if (a[i - 1] == color) {
            running[color][0]++;
            running[color][2] = i;
            continue;
        }

        if (running[color][2] + 1 != left_same_index) {
            best[color] = std::max(best[color], running[color][0]);
            running[color][0] = 1;
            running[color][1] = -1;
            running[color][2] = i;
            left_same_index = i;
            continue;
        }

        if (running[color][1] == -1 || running[color][1] == a[left_same_index]) {
            running[color][0]++;
            running[color][1] = a[left_same_index];
            running[color][2] = i;
            left_same_index = i;
            continue;
        }

        best[color] = std::max(best[color], running[color][0]);
        running[color][0] = 2;
        running[color][1] = a[left_same_index];
        running[color][2] = i;
        left_same_index = i;
    }

    int res = 0;
    for (auto& [color, data] : running) {
        res = std::max(res, std::max(best[color], data[0]));
    }

    std::cout << res;
}