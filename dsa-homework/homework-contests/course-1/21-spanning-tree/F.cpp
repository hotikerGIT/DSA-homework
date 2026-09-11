#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#define int long long

signed main() {
    int n;
    std::cin >> n;
    std::vector<int> red, green, blue;
    int min_green = 2e9, max_green = 0;

    for (int i = 0; i < n; ++i) {
        int x; char color;
        std::cin >> x >> color;

        if (color == 'R') {
            red.push_back(x);
        } else if (color == 'B') {
            blue.push_back(x);
        } else {
            min_green = std::min(min_green, x);
            max_green = std::max(max_green, x);
            green.push_back(x);
        }
    }

    int ans = 0;

    if (green.empty()) {
        if (!red.empty()) ans = red.back() - red.front();
        if (!blue.empty()) ans += blue.back() - blue.front();

        std::cout << ans;
        return 0;
    }

    std::vector<std::vector<int>> segments(2, std::vector<int>(green.size() - 1));

    auto color_count = [&](std::vector<int>& colors, int color) {
        if (!colors.empty()) {
            if (green.front() > colors.front()) {
                ans += green.front() - colors.front();
            }

            if (green.back() < colors.back()) {
                ans += colors.back() - green.back();
            }
        }

        for (int green_index = 0; green_index + 1 < green.size(); ++green_index) {
            int left_color_index = std::lower_bound(colors.begin(), colors.end(), green[green_index]) - colors.begin();
            int right_color_index = std::upper_bound(colors.begin(), colors.end(), green[green_index + 1]) - colors.begin() - 1;

            if (left_color_index >= colors.size()
                || colors[left_color_index] > green[green_index + 1]
                || right_color_index < left_color_index)
            {
                segments[color][green_index] = green[green_index + 1] - green[green_index];
                continue;
            }

            int best_dist = std::max(colors[left_color_index] - green[green_index], green[green_index + 1] - colors[right_color_index]);
            for (int i = left_color_index + 1; i <= right_color_index; ++i) {
                best_dist = std::max(best_dist, colors[i] - colors[i - 1]);
            }

            segments[color][green_index] = best_dist;
        }
    };

    color_count(red, 0);
    color_count(blue, 1);

    for (int i = 0; i < green.size() - 1; ++i) {
        int delta = green[i + 1] - green[i];
        ans += std::min(3 * delta - segments[0][i] - segments[1][i], 2 * delta);
    }

    std::cout << ans;
}