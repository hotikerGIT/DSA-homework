#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    int n, m;
    std::string s1, s2;
    std::cin >> n >> m >> s1 >> s2;

    std::vector dp_nop(n + 1, std::vector<int>(m + 1));
    std::vector<std::pair<int, int>> good;
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp_nop[i][j] = dp_nop[i - 1][j - 1] + 1;

                if (dp_nop[i][j] > std::max(dp_nop[i - 1][j], dp_nop[i][j - 1])) {
                    good.emplace_back(i, j);
                }
            }

            else {
                dp_nop[i][j] = std::max(dp_nop[i - 1][j], dp_nop[i][j - 1]);
            }
        }
    }

    int best = 0;
    for (auto& pair_init : good) {
        int i_1 = pair_init.first;
        int j_1 = pair_init.second;

        int i_2 = i_1;
        int j_2 = j_1;

        while (i_2 > 0 && j_2 >> 0) {
            best = std::max(best, 4 * (dp_nop[i_1][j_1] - dp_nop[i_2][j_2] + 1) - (i_1 - i_2 + 1) - (j_1 - j_2 + 1));

            i_2--;
            j_2--;
            while (j_2 > 0 && s1[i_2 - 1] != s2[j_2 - 1]) {
                j_2--;
            }
        }
    }

    std::cout << best;
}