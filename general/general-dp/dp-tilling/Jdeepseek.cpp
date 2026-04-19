#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    if (n > m) {
        vector<string> new_grid(m, string(n, ' '));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                new_grid[j][i] = grid[i][j];
            }
        }
        grid = new_grid;
        swap(n, m);
    }

    int size = 1 << n;
    // dp[mask][has_guard_above][unc]
    vector<vector<vector<int>>> dp(size, vector<vector<int>>(2, vector<int>(2, 0)));
    dp[0][0][0] = 1;

    for (int c = 0; c < m; c++) {
        for (int r = 0; r < n; r++) {
            vector<vector<vector<int>>> new_dp(size, vector<vector<int>>(2, vector<int>(2, 0)));

            for (int mask = 0; mask < size; mask++) {
                for (int has_above = 0; has_above < 2; has_above++) {
                    for (int unc = 0; unc < 2; unc++) {
                        if (dp[mask][has_above][unc] == 0) continue;
                        int cur = dp[mask][has_above][unc];

                        if (grid[r][c] == 'x') {
                            int new_mask = mask & ~(1 << r);
                            int new_has_above = 0;
                            new_dp[new_mask][new_has_above][unc] = (new_dp[new_mask][new_has_above][unc] + cur) % MOD;

                        } else {
                            bool guarded = (mask & (1 << r)) || has_above;

                            if (guarded) {
                                int new_has_above = has_above;
                                new_dp[mask][new_has_above][unc] = (new_dp[mask][new_has_above][unc] + cur) % MOD;
                                int new_mask = mask | (1 << r);
                                new_dp[new_mask][1][unc] = (new_dp[new_mask][1][unc] + cur) % MOD;

                            } else {
                                if (unc == 0) {
                                    int new_has_above = has_above;
                                    new_dp[mask][new_has_above][1] = (new_dp[mask][new_has_above][1] + cur) % MOD;
                                }

                                int new_mask = mask | (1 << r);
                                new_dp[new_mask][1][unc] = (new_dp[new_mask][1][unc] + cur) % MOD;
                            }
                        }
                    }
                }
            }
            dp = move(new_dp);
        }

        vector<vector<vector<int>>> next_dp(size, vector<vector<int>>(2, vector<int>(2, 0)));
        for (int mask = 0; mask < size; mask++) {
            for (int unc = 0; unc < 2; unc++) {
                next_dp[mask][0][unc] = (next_dp[mask][0][unc] + dp[mask][0][unc]) % MOD;
                next_dp[mask][0][unc] = (next_dp[mask][0][unc] + dp[mask][1][unc]) % MOD;
            }
        }

        dp = move(next_dp);
    }

    int ans = 0;
    for (int mask = 0; mask < size; mask++) {
        for (int has_above = 0; has_above < 2; has_above++) {
            ans = (ans + dp[mask][has_above][0]) % MOD;
            ans = (ans + dp[mask][has_above][1]) % MOD;
        }
    }
    cout << ans << endl;

    return 0;
}