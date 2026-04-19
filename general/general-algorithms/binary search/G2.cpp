#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    int res = 0;
    int L = 0;
    for (int num : b) {
        int left = L;
        int right = n - 1;
        int weight = 1 << num;

        while (left <= right) {
            int middle = (left + right) / 2;

            if (a[middle] >= weight) {
                right = middle - 1;
            }

            else {
                left = middle + 1;
            }
        }

        if (left == n || a[left] < weight) {
            break;
        }

        res++;
        L = left + 1;
    }

    std::cout << res;
}