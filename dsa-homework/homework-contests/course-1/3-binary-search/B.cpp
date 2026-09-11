#include <iostream>
#include <vector>

int main() {
    int t, n, q, i, k, middle;
    std::cin >> t;

    for (int j = 0; j < t; ++j) {
        std::cin >> n >> q;

        std::vector<int> a(n);
        for (int index = 0; index < n; ++index) {
            std::cin >> a[index];
        }

        std::vector<std::vector<int>> dp(n);
        int left = 0;
        int right = 1;

        int round = 1;
        bool no_ultimate_winner_flag = true;
        while (no_ultimate_winner_flag) {
            no_ultimate_winner_flag = a[left] != n && a[right] != n;

            if (a[left] < a[right]) {
                left = right;
            }

            dp[left].push_back(round);

            right++;
            round++;
        }

        for (int query = 0; query < q; ++query) {
            std::cin >> i >> k;

            std::vector<int>& contestant = dp[i - 1];
            left = 0;
            right = (int)contestant.size() - 1;

            while (left <= right) {
                middle = (left + right) / 2;

                if (contestant[middle] > k) {
                    right = middle - 1;
                }

                else {
                    left = middle + 1;
                }
            }

            if (a[i - 1] == n && left == contestant.size()) {
                left += k - contestant[left - 1];
            }

            std::cout << left << std::endl;
        }
    }
}