#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n, m;
    std::cin >> n >> m;
    if (m < n) std::swap(n, m);
    if ((n * m) % 2 == 1 || n * m < 4) {
        std::cout << 0 << std::endl;
        return 0;
    }

    int profile_bits = 2 * (n + 1);
    std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(m + 1, std::vector<int>(1 << profile_bits, 0)));
    dp[0][0][0] = 1;  // ИСПРАВЛЕНО: начинаем с (0,0) и пустого профиля

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            for (int p = 0; p < (1 << profile_bits); ++p) {
                if (dp[i][j][p] == 0) continue;

                int pos = 2 * i;
                int left_bit = (p >> pos) & 1;
                int up_bit = (p >> (pos + 1)) & 1;

                if (i == 0) up_bit = 0; // В первой строке нет сверху
                if (j == 0) left_bit = 0; // В первом столбце нет слева

                // Варианты: труба может идти вправо, вниз, или поворачивать
                if (!left_bit && !up_bit) {
                    // Начало новой трубы - может идти вправо или вниз
                    if (i < n - 1) { // вниз
                        int new_p = p | (1 << (pos + 1));
                        dp[i + 1][j][new_p] += dp[i][j][p];
                    }
                    if (j < m - 1) { // вправо
                        int new_p = p | (1 << pos);
                        if (i == n - 1) {
                            dp[0][j + 1][new_p << 2] += dp[i][j][p];
                        } else {
                            dp[i + 1][j][new_p] += dp[i][j][p];
                        }
                    }
                } else if (left_bit && !up_bit) {
                    // Труба пришла слева - может идти вправо, вниз или наверх
                    if (i < n - 1) { // вниз
                        int new_p = (p & ~(1 << pos)) | (1 << (pos + 1));
                        dp[i + 1][j][new_p] += dp[i][j][p];
                    }
                    if (j < m - 1) { // вправо
                        int new_p = p; // продолжаем вправо
                        if (i == n - 1) {
                            dp[0][j + 1][new_p << 2] += dp[i][j][p];
                        } else {
                            dp[i + 1][j][new_p] += dp[i][j][p];
                        }
                    }
                    if (i > 0) { // наверх - завершаем
                        int new_p = p & ~(1 << pos);
                        dp[i - 1][j][new_p] += dp[i][j][p];
                    }
                } else if (!left_bit && up_bit) {
                    // Труба пришла сверху - может идти вправо, вниз или налево
                    if (i < n - 1) { // вниз
                        int new_p = p; // продолжаем вниз
                        dp[i + 1][j][new_p] += dp[i][j][p];
                    }
                    if (j < m - 1) { // вправо
                        int new_p = (p & ~(1 << (pos + 1))) | (1 << pos);
                        if (i == n - 1) {
                            dp[0][j + 1][new_p << 2] += dp[i][j][p];
                        } else {
                            dp[i + 1][j][new_p] += dp[i][j][p];
                        }
                    }
                    if (j > 0) { // налево - завершаем
                        int new_p = p & ~(1 << (pos + 1));
                        dp[i][j - 1][new_p] += dp[i][j][p];
                    }
                } else { // left_bit && up_bit
                    // Угол - завершаем соединение
                    int new_p = p & ~(1 << pos) & ~(1 << (pos + 1));
                    if (i == n - 1 && j == m - 1) {
                        // Последняя клетка - проверяем замкнутость
                        if (new_p == 0) {
                            dp[i][j + 1][new_p] += dp[i][j][p];
                        }
                    } else {
                        if (i == n - 1) {
                            dp[0][j + 1][new_p << 2] += dp[i][j][p];
                        } else {
                            dp[i + 1][j][new_p] += dp[i][j][p];
                        }
                    }
                }
            }
        }
    }

    // Ответ - количество способов закончить в последней клетке с пустым профилем
    std::cout << dp[n - 1][m][0] << std::endl;
    return 0;
}