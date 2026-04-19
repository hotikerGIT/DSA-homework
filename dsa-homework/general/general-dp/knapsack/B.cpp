#include <iostream>
#include <vector>

long long recursion(std::vector<long long>& counts,
                    std::vector<long long>& dp,
                    std::vector<int>& used,
                    long long w,
                    long long cur_w,
                    int cur_num)
{

    if (used[cur_num] > 8) {
        return recursion(counts, dp, used, w, cur_w, cur_num - 1);
    }

    if (cur_num == 0) {
        return cur_w;
    }

    int margin = cur_w - w;
    int big_index = 8;
    long long res = std::max(w - 7, 0LL);

    // попытаемся найти способ убрать margin
    for (int i = margin; i < 8; ++i) {
        for (int j = 0; j < big_index - margin; ++j) {
            if (dp[big_index - j] && counts[big_index - j - i]) {
                res = std::max(cur_w - i, res);

                dp[big_index - j]--;
                counts[big_index - j - i]--;
                used[cur_num]++;

                res = std::max(recursion(counts, dp, used, w, cur_w - i, cur_num), res);

                used[cur_num]--;
                dp[big_index - j]++;
                counts[big_index - j - i]++;
            }
        }
    }

    return res;
}

int main() {
    long long w;
    std::cin >> w;

    std::vector<long long> counts(9);
    counts[0] = 100;

    for (int i = 1; i < 9; ++i) {
        std::cin >> counts[i];
    }

    long long total_sum = 0;
    for (int i = 1; i <= 8; ++i) {
        total_sum += counts[i] * i;
    }

    if (total_sum <= w) {
        std::cout << total_sum;
        return 0;
    }

    std::vector<long long> dp(9);
    int cur = 8;
    long long temp = w;

    std::vector<int> used(9, 0);  // сколько использовано

    // берем веса которые можем (с перебором)
    while (temp > 0) {
        dp[cur] = std::min(counts[cur], (temp + cur - 1) / cur);
        temp -= dp[cur] * cur;
        counts[cur] -= dp[cur];
        cur--;
    }

    std::cout << recursion(counts, dp, used, w, w - temp, 8);
}