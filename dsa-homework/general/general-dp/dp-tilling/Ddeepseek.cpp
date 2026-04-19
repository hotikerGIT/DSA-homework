#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int m, n;
long long dp[1<<8][2][1<<8]; // [mask][col_cut][row_cut_mask]

int main() {
    cin >> m >> n;
    if (m > n) swap(m, n);

    int size = 1 << m;
    int row_size = 1 << (m-1);

    memset(dp, 0, sizeof(dp));
    dp[0][1][0] = 1; // Начальное состояние

    for (int col = 0; col < n; col++) {
        for (int row = 0; row < m; row++) {
            long long new_dp[1<<8][2][1<<8];
            memset(new_dp, 0, sizeof(new_dp));

            for (int mask = 0; mask < size; mask++) {
                for (int col_cut = 0; col_cut < 2; col_cut++) {
                    for (int row_cut = 0; row_cut < row_size; row_cut++) {
                        if (dp[mask][col_cut][row_cut] == 0) continue;
                        long long cur = dp[mask][col_cut][row_cut];

                        int pos = 1 << row;

                        // Клетка уже покрыта горизонтальной доминошкой слева
                        if (mask & pos) {
                            int new_mask = mask & ~pos;
                            new_dp[new_mask][col_cut][row_cut] += cur;
                            continue;
                        }

                        // Вертикальная доминошка
                        if (row < m-1 && !(mask & (1 << (row+1)))) {
                            int new_mask = mask;
                            int new_row_cut = row_cut | (1 << row);
                            new_dp[new_mask][col_cut][new_row_cut] += cur;
                        }

                        // Горизонтальная доминошка
                        int new_mask = mask | pos;
                        new_dp[new_mask][1][row_cut] += cur;
                    }
                }
            }
            memcpy(dp, new_dp, sizeof(dp));
        }

        // Конец столбца
        long long next_dp[1<<8][2][1<<8];
        memset(next_dp, 0, sizeof(next_dp));

        for (int mask = 0; mask < size; mask++) {
            if (mask != 0) continue; // Все горизонтальные доминошки должны быть завершены

            for (int col_cut = 0; col_cut < 2; col_cut++) {
                for (int row_cut = 0; row_cut < row_size; row_cut++) {
                    if (col_cut) { // Должен быть вертикальный разрез
                        next_dp[0][0][row_cut] += dp[mask][col_cut][row_cut];
                    }
                }
            }
        }
        memcpy(dp, next_dp, sizeof(dp));
    }

    // В конце проверяем все горизонтальные разрезы
    int full_row_cut = (1 << (m-1)) - 1;
    long long ans = 0;

    for (int mask = 0; mask < size; mask++) {
        for (int col_cut = 0; col_cut < 2; col_cut++) {
            for (int row_cut = 0; row_cut < row_size; row_cut++) {
                if (row_cut == full_row_cut) {
                    ans += dp[mask][col_cut][row_cut];
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}