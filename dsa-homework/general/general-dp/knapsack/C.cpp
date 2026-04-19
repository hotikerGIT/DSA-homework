#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    int up = 0;
    int down = 0;
    int cur_sum = a[0] - b[0];
    std::vector<std::vector<std::pair<int, int>>> seen(2, std::vector<std::pair<int, int>>(n, {-1, -1}));
    seen[0][0] = {0, 0};
    seen[1][0] = {0, 0};

    while (up < n && down < n) {
        int check = (cur_sum >= 0) ? 1 : 0;
        int abs_sum = std::abs(cur_sum);

        if (seen[check][abs_sum].first != -1) {
            int left1 = seen[check][abs_sum].first;
            int left2 = up;
            int right1 = seen[check][abs_sum].second;
            int right2 = down;

            std::cout << left2 - left1 + 1 << "\n";
            for (int i = left1; i <= left2; ++i) {
                std::cout << i + 1 << " ";
            }
            std::cout << "\n";

            std::cout << right2 - right1 + 1 << "\n";
            for (int i = right1; i <= right2; ++i) {
                std::cout << i + 1 << " ";
            }
            std::cout << "\n";
            return 0;
        }

        seen[check][abs_sum] = {up + 1, down + 1};

        if (cur_sum < 0) {
            if (up == n - 1) break;
            up++;
            cur_sum += a[up];
        } else {
            if (down == n - 1) break;
            down++;
            cur_sum -= b[down];
        }
    }
}