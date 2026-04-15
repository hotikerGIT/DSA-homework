#include <iostream>
#include <vector>
#define int long long

signed main() {
    freopen("m3.in", "r", stdin);
    freopen("m3.out", "w", stdout);

    const int mod = (1LL << 30) + 1;
    int n, m;
    std::cin >> n >> m;
    if (m < n) std::swap(n, m);

    if (m == 1) {
        std::cout << 2;
        return 0;
    }

    // dp[i][j][p]
    std::vector dp(n, std::vector(m, std::vector<int>(1LL << (n + 1))));
    for (int p = 0; p < 1LL << (n + 1); ++p) {
        dp[0][1][p] = 1;
    }

    for (int j = 1; j < m; ++j) { // column
        for (int i = 1; i < n; ++i) { // row
            for (int p = 0; p < 1LL << (n + 1); ++p) { // mask
                for (int color = 0; color < 2; ++color) { // color
                    if ((p >> (i - 1) & 7) == color * 7) continue;
                    int next_p = (p & ~(1LL << i)) | (color << i);

                    dp[i][j][next_p] = (dp[i][j][next_p] + dp[i - 1][j][p]) % mod;
                }
            }
        }

        if (j == m - 1) continue;
        for (int p = 0; p < 1LL << (n + 1); ++p) {
            int next_p = p << 1LL;
            next_p &= (1LL << (n + 1)) - 1;
            dp[0][j + 1][next_p] += dp[n - 1][j][p];
            dp[0][j + 1][next_p + 1] += dp[n - 1][j][p];

            dp[0][j + 1][next_p] %= mod;
            dp[0][j + 1][next_p] %= mod;
        }

        // if (j == m - 1) continue;
        // for (int p = 0; p < 1 << (n + 1); ++p) dp[0][j + 1][p] += dp[n - 1][j][p];

        // if (j == m - 1) continue;
        //
        // for (int p = 0; p < 1 << (n + 1); ++p) {
        //     dp[0][j + 1][p] = last;
        // }
    }

    int answ = 0 ;
    for (auto el: dp[n - 1][m - 1]) {
        answ += el;
        answ %= mod;
    }
    std::cout << answ << std::endl;

    return 0;
}