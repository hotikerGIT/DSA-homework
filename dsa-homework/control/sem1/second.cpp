#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<long long> a(n);
    long long res_sum = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        res_sum += a[i];
    }

    if (res_sum % k != 0) {
        std::cout << -1;
        return 0;
    }

    long long target_sum = res_sum / k;

    // предпосчет масок. Будем сохранять лишь те маски, что достигают необходимой суммы
    std::vector<int> masks;
    for (int i = 0; i < 1 << n; ++i) {
        int mask = i;
        long long sum = 0;

        for (int j = 0; j < n; ++j) {
            if ((mask >> j) & 1) {
                sum += a[j];
            }
        }

        if (sum == target_sum) masks.push_back(mask);
    }

    // итый слой - сколько взяли групп. Житый индекс - из какой маски перешли в маску жи.
    std::vector<std::vector<int>> dp(k + 1, std::vector<int>(1 << n, -1));
    dp[0][0] = 0;

    for (int i = 0; i < k; ++i) {
        for (int dp_mask = 0; dp_mask < 1 << n; ++dp_mask) {
            if (dp[i][dp_mask] == -1) continue;

            for (int mask : masks) {
                if ((mask & dp_mask) != 0) continue;
                dp[i + 1][mask | dp_mask] = mask;
            }
        }
    }

    // делаем вывод
    std::vector<int> result(n, 0);
    int cur_mask = (1 << n) - 1;

    if (dp[k][cur_mask] == -1) {
        std::cout << -1;
        return 0;
    }

    int color = k;
    for (int i = k; i > 0; --i) {
        int next_mask = dp[i][cur_mask];

        for (int j = 0; j < n; ++j) {
            if ((next_mask >> j) & 1) {
                result[j] = color;
            }
        }

        cur_mask ^= next_mask;
        color--;
    }

    for (int num : result) {
        std::cout << num << ' ';
    }
    std::cout << std::endl;
}