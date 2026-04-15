#include <iostream>
#include <vector>

int main() {
    int n, l, r, x;
    std::cin >> n >> l >> r >> x;

    std::vector<int> c(n);
    for (int i = 0; i < n; ++i) std::cin >> c[i];

    int ans = 0;
    for (int mask = 1; mask < 1 << n; ++mask) {
        int i = mask;
        int count = 0;
        int min = 1e6;
        int max = 0;
        int sum = 0;
        int index = -1;

        while (i > 0) {
            int bit = i & 1;
            i >>= 1;
            index++;
            if (!bit) continue;

            count++;
            min = std::min(min, c[index]);
            max = std::max(max, c[index]);
            sum += c[index];
        }

        if (sum >= l && sum <= r && count >= 2 && max - min >= x) {
            ans++;
        }
    }

    std::cout << ans;
}