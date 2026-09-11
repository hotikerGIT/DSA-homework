#include <iostream>
#include <vector>
#include <deque>

int distance(std::vector<std::pair<int, int>>& points, int index1, int index2) {
    int x1 = points[index1].first;
    int x2 = points[index2].first;
    int y1 = points[index1].second;
    int y2 = points[index2].second;

    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    int xs, ys;
    std::cin >> xs >> ys;

    int n;
    std::cin >> n;
    int answer = 0;

    std::vector<std::pair<int, int>> coords(n + 1);
    std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(n + 1, 0));
    coords[0] = {xs, ys};

    for (int i = 1; i <= n; ++i) {
        int x, y;
        std::cin >> x >> y;
        coords[i] = {x, y};
        answer += distance(coords, i, 0);
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == j) {
                matrix[i][j] = distance(coords, i, 0);
            }

            else {
                matrix[i][j] = distance(coords, i, j);
            }
        }
    }

    std::vector<std::vector<int>> masks(n + 1);
    for (int i = 0; i < 1 << n; ++i) {
        int mask = i;
        int bit_count = 0;

        for (int j = 0; j < n; ++j) {
            if (mask >> j & 1) bit_count++;
        }

        masks[bit_count].push_back(i);
    }

    std::vector<std::pair<int, int>> dp(1 << n, {1e6, -1});
    dp[0] = {0, -1};

    for (int i = 0; i < n; i++) {
        for (int mask : masks[i]) {
            if (dp[mask].first == 1e6) continue;

            for (int new_index = 0; new_index < n; new_index++) {
                if (mask >> new_index & 1 || mask >> i & 1) continue;

                int new_mask = mask | (1 << new_index) | (1 << i);
                int new_value = dp[mask].first + matrix[i + 1][new_index + 1];

                if (new_value < dp[new_mask].first) {
                    dp[new_mask] = {new_value, mask};
                }
            }
        }
    }

    int cur_mask = (1 << n) - 1;
    int start = n - 1;
    std::deque<int> out;

    while (cur_mask > 0) {
        out.push_front(0);
        int next_mask = dp[cur_mask].second;
        int index_mask = cur_mask ^ next_mask;

        std::vector<int> bits;
        for (int j = 0; j < n; ++j) {
            if (index_mask >> j & 1) {
                bits.push_back(j);
            }
        }

        for (int bit : bits) {
            out.push_front(bit + 1);
        }

        cur_mask = next_mask;
        start -= bits.size();
    }
    out.push_front(0);

    std::cout << answer + dp[(1 << n) - 1].first << '\n';
    for (int num : out) {
        std::cout << num << ' ';
    }
}
