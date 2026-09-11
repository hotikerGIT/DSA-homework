#include <iostream>
#include <vector>

int main() {
    const int mod = 1e9 + 9;
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(m + 1, 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            std::cin >> c;
            if (c == 'x') {
                matrix[i][j] = 1;
            }

            else {
                matrix[i][j] = 0;
            }
        }
    }

    // для дальнейшей быстрой (О(1)) проверки на правильность профиля
    // (не поставлен охранник на стенке) переведем битовую матрицу в перевернутый массив битов
    std::vector<int> bitset(m + 1);
    bitset[0] = 0;
    for (int i = 0; i < m; ++i) {
        int num = 0;
        for (int j = 0; j < n; ++j) {
            num |= matrix[j][i] << j;
        }
        bitset[i + 1] = num;
    }

    // в профиле будем хранить также, пропускали ли мы уже одну клетку, или еще нет.
    std::vector dp(n, std::vector(m, std::vector(1 << (n + 1), std::vector(2, 0))));
    // в базе два случая - ставить охранника или не ставить
    // если можем поставить и ставим, то клетка никогда не будет пропущена
    // если можем поставить и не ставим, то клетка всегда будет пропущена
    if (matrix[0][0] == 1) {
        dp[0][0][0][0] = 1;
    }
    else {
        dp[0][0][0][1] = 1;
        dp[0][0][1][0] = 1;
    }

    for (int j = 0; j < m; ++j) {
        for (int i = 1; i < n; ++i) {
            if (matrix[i][j] == 1) {
                dp[i][j] = dp[i - 1][j];
                continue;
            }

            int correct_profile = bitset[j + 1] & (1 << (n - i)) - 1 | bitset[j] >> (n - i) << (n - i);
            for (int p = 0; p <= correct_profile; p = (p + 1) & correct_profile) {
                for (int skipped = 0; skipped < 2; ++skipped) {
                    // поставить охранника можем всегда
                    dp[i][j][p | 1 << i][skipped] += dp[i][j][p][skipped];

                    // если сверху и слева уже кто-то стоит, то мы можем не ставить охранника
                    // или же кто-то стоит с одной стороны, а с другой стороны стена
                    if ((p & 1 << (i - 1) && p & 1 << (i + 1)) ||
                        (p & 1 << (i + 1) && matrix[i + 1][j] == 1) ||
                        (p & 1 << (i - 1) && matrix[i][j + 1] == 1)) {
                        dp[i][j][p & ~(1 << i)][skipped] += dp[i][j][p][skipped];
                    }

                    // иначе можем не ставить охранника и увеличить скип
                    else if (!skipped){
                        dp[i][j][p & ~(1 << i)][1] += dp[i][j][p][skipped];
                    }
                }

                if (p == correct_profile) break;
            }
        }

        if (j == m - 1) continue;

        int incorrect_profile = bitset[j + 1] | bitset[j] & 1 << n;
        int correct_profile = ~incorrect_profile;
        for (int p = 0; p <= correct_profile; p = (p + 1) & correct_profile) {
            for (int skipped = 0; skipped < 2; ++skipped) {
                int next_p = p << 1 & ((1 << (n + 1)) - 1);

                if (matrix[0][j + 1] == 1) dp[0][j + 1][next_p][skipped] += dp[n - 1][j][p][skipped];
                else {
                    dp[0][j + 1][next_p + 1][skipped] += dp[n - 1][j][p][skipped];

                    if (p & 1 && matrix[1][j + 1] == 1) {
                        dp[0][j + 1][next_p][skipped] += dp[n - 1][j][p][skipped];
                    }
                    else if (!skipped) dp[0][j + 1][next_p][1] += dp[n - 1][j][p][skipped];;
                }
            }

            if (p == correct_profile) break;
        }
    }

    int ans = 0;
    for (int p = 0; p < 1 << (n + 1); ++p) {
        for (int skipped = 0; skipped < 2; ++skipped) {
            ans = (ans + dp[n - 1][m - 1][p][skipped]) % mod;
        }
    }
    std::cout << ans << std::endl;
}