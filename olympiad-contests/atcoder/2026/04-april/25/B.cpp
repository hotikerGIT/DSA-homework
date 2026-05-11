#include <iostream>
#include <string>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> strings(n);
    for (int i = 0; i < n; ++i) std::cin >> strings[i];

    int ans = 0;
    for (int h1 = 0; h1 < n; ++h1) {
        for (int h2 = h1; h2 < n; ++h2) {
            for (int w1 = 0; w1 < m; ++w1) {
                for (int w2 = w1; w2 < m; ++ w2) {
                    bool flag = true;

                    for (int i = h1; i <= h2; ++i) {
                        for (int j = w1; j <= w2; ++j) {
                            if (strings[h1 + h2 - i][w1 + w2 - j] != strings[i][j]) {
                                flag = false;
                                break;
                            }
                        }
                    }

                    ans += flag;
                }
            }
        }
    }

    std::cout << ans;
}