#include <iostream>
#include <vector>
#define int long long

bool check(int a, int size, int mid, int n) {
    int prod = 1;
    int index = 0;

    while (prod <= 1 + n / (a + index * mid) && index < size) {
        prod *= a + index * mid;
        index++;
    }

    if (prod <= n && index == size) return true;
    return false;
}

signed main() {
    int n;
    std::cin >> n;

    int ans = 0;
    int max_size = 20;
    for (int a = 1; a * a * a <= n; ++a) {
        for (int size = 3; size <= max_size; ++size) {
            int left = 1;
            int right = n;
            int k = 0;

            while (left <= right) {
                int mid = (left + right) / 2;

                if (check(a, size, mid, n)) {
                    k = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            ans += k;
            if (k == 0) {
                max_size = size;
                break;
            }

        }
    }

    std::cout << ans;
}