#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int lcis_length(const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    int m = b.size();

    // dp[j] - длина LCIS для текущего i, заканчивающейся в b[j]
    vector<int> dp(m, 0);

    for (int i = 0; i < n; i++) {
        int current_best = 0;  // лучший результат для элементов меньше a[i]

        for (int j = 0; j < m; j++) {
            // Сохраняем предыдущее значение dp[j] перед возможным обновлением
            int prev_dp = dp[j];

            // Если элементы равны, можем увеличить подпоследовательность
            if (a[i] == b[j]) {
                dp[j] = max(dp[j], current_best + 1);
            }

            // Если b[j] меньше a[i], он может быть предком для будущих совпадений
            if (b[j] < a[i]) {
                current_best = max(current_best, prev_dp);
            }
        }
    }

    // Находим максимальное значение в dp
    int result = 0;
    for (int val : dp) {
        result = max(result, val);
    }

    return result;
}

int main() {
    int n, m;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::cin >> m;
    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) std::cin >> b[i];

    std::cout << lcis_length(a, b);

    return 0;
}