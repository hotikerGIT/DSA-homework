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

    std::vector<int> cnt(n + 5);
    std::vector<int> color(n + 5);
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            color[cur] = a[i];
            cnt[cur] = 1;
            continue;
        }

        if (a[i] == a[i - 1]) {
            cnt[cur]++;
        } else {
            cur++;
            cnt[cur] = 1;
            color[cur] = a[i];
        }
    }

    std::vector<std::pair<int, int>> dp(n);
    dp[0] = { cnt[0], -1 };
    dp[1] = { cnt[1], -1 };
    for (int i = 2; i < n; ++i) {
        dp[i] = { cnt[i], -1 };

        if (color[i - 2] == color[i]) {
            dp[i] = { cnt[i] + cnt[i - 2], color[i - 1]};

            if (dp[i - 2].second == -1 || dp[i - 2].second == color[i - 1]) {
                dp[i] = { cnt[i] + dp[i - 2].first, color[i - 1] };
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = std::max(res, dp[i].first);
    }

    std::cout << res;
}