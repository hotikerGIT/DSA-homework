#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

const int LIM = (int)4e18;

// Биномиальный коэффициент с ограничением сверху, чтобы избежать переполнения
int C(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    __int128 res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - k + i) / i;
        if (res > (__int128)LIM) return LIM;
    }
    return (int)res;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    // Шаг 1: находим длину p искомой подпоследовательности,
    // вычитая C(n, i) пока k больше этого числа
    int p = 0;
    for (int i = 1; i <= n; ++i) {
        int c = C(n, i);
        if (k > c) {
            k -= c;
        } else {
            p = i;
            break;
        }
    }

    if (p == 0) {
        std::cout << -1 << '\n';
        return 0;
    }

    // Шаг 2: строим ответ длины p
    std::vector<int> ans;
    int start = 0;   // начало рассматриваемого суффикса в исходном массиве
    int rem = p;     // сколько ещё символов нужно выбрать
    int kk = k;      // текущий номер внутри подпоследовательностей длины p

    while (rem > 0) {
        // Сортируем префикс a[start .. n - rem]
        // (не содержит суффикс размера rem, из которого ещё нужно добрать rem элементов)
        std::vector<std::pair<int,int>> sp;
        for (int i = start; i <= n - rem; ++i) {
            sp.push_back({a[i], i});
        }
        std::sort(sp.begin(), sp.end());

        int chosen = -1;
        for (auto &pr : sp) {
            int val = pr.first;
            int idx = pr.second;
            // Сколько подпоследовательностей длины rem-1 можно составить
            // из оставшихся после idx элементов
            int cnt = C(n - idx - 1, rem - 1);
            if (kk > cnt) {
                kk -= cnt;
            } else {
                ans.push_back(val);
                chosen = idx;
                break;
            }
        }

        if (chosen == -1) {
            // На всякий случай, если идея дала сбой
            std::cout << -1 << '\n';
            return 0;
        }

        start = chosen + 1;
        rem--;
    }

    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) std::cout << ' ';
        std::cout << ans[i];
    }
    std::cout << '\n';

    return 0;
}