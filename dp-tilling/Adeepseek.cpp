#include <iostream>
#include <vector>
#define int long long

bool has_single_component(int p, int n) {
    int active = 0;
    for (int i = 0; i <= n; i++) {
        if (p & (1 << (2*i))) active++;     // горизонтальные требования
        if (p & (1 << (2*i + 1))) active++; // вертикальные требования
    }
    // Главное - четное число активных требований (они должны образовывать пары)
    return (active % 2 == 0);
}

signed main() {
    int n, m;
    std::cin >> n >> m;
    if (m < n) std::swap(n, m);
    if ((n * m) % 2 == 1 || n < 2) {
        std::cout << 0 << std::endl;
        return 0;
    }

    int profile_bits = 2 * (n + 1);
    std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(m, std::vector<int>(1 << profile_bits, 0)));
    dp[0][0][3] = 1;

    for (int j = 0; j < m; ++j) {
        for (int i = 1; i < n; ++i) {
            for (int p = 0; p < (1 << profile_bits); ++p) {
                if (dp[i-1][j][p] == 0) continue;

                int vertical_bit = p & (1 << (2 * (i - 1) + 1));
                int horizontal_bit = p & (1 << (2 * (i + 1)));

                int next_p;
                int second_p = -1;
                if (!vertical_bit && !horizontal_bit) {
                    next_p = p | (1 << (2 * i)) | (1 << (2 * i + 1));
                }
                else if (vertical_bit && horizontal_bit) {
                    next_p = p & ~(1 << (2 * i)) & ~(1 << (2 * i + 1));
                }
                else {
                    next_p = p & ~(1 << (2 * i)) | (1 << (2 * i + 1));
                    second_p = p & ~(1 << (2 * i + 1)) | (1 << (2 * i));
                }

                // ПРОВЕРКА: если последняя строка, нельзя создавать вертикальное требование
                bool next_valid = true;
                bool second_valid = true;

                if (i == n - 1) {
                    // В последней строке проверяем, не создаём ли вертикальное требование
                    if (next_p & (1 << (2 * i + 1))) next_valid = false;
                    // ДОЛЖНО БЫТЬ:
                    if (second_p != -1 && (second_p & (1 << (2 * i + 1)))) second_valid = false;
                }

                if (j == m - 1) {
                    if (next_p & (1 << (2 * i))) next_valid = false;
                    if (second_p != -1 && (second_p & (1 << (2 * i)))) second_valid = false;
                }

                // ДОБАВЛЕНО ПРОВЕРКИ НА ЕДИНСТВЕННОСТЬ КОМПОНЕНТЫ
                if (next_valid && has_single_component(next_p, n)) {
                    dp[i][j][next_p] += dp[i-1][j][p];
                }

            }
        }

        if (j == m - 1) continue;
        for (int p = 0; p < (1 << profile_bits); ++p) {
            if (dp[n-1][j][p] == 0) continue;

            int next_p = (p << 2) & ((1 << profile_bits) - 1);

            // ДОБАВЛЕНО ПРОВЕРКИ НА ЕДИНСТВЕННОСТЬ КОМПОНЕНТЫ
            if (next_p & (1 << 2)) {
                if (j != m - 2 && has_single_component(next_p | 1, n)) {
                    dp[0][j + 1][next_p | 1] += dp[n-1][j][p];
                }
                if (has_single_component(next_p | 2, n)) {
                    dp[0][j + 1][next_p | 2] += dp[n-1][j][p];
                }
            }
            else {
                if (has_single_component(next_p | 3, n)) {
                    dp[0][j + 1][next_p | 3] += dp[n-1][j][p];
                }
            }
        }
    }

    long long ans = 0;
    for (int p = 0; p < (1 << profile_bits); ++p) {
        int num = dp[n-1][m-1][p];

        bool flag = true;
        for (int i = 0; i < n; ++i) {
            if (p & (1 << (2 * i))) {
                flag = false;
                break;
            }
        }

        // ДОБАВЛЕНО: проверяем что компонента одна (пустой профиль = одна замкнутая компонента)
        if (flag) {
            ans += num;
        }
    }

    std::cout << ans << std::endl;
    return 0;
}