#include <iostream>
#include <vector>

int main() {
    long long n;
    std::cin >> n;

    long long ans = n;
    std::vector<int> need = {2, 3, 5, 7};

    for (int mask = 1; mask < 1 << 4; ++mask) {
        int i = mask;

        int count = 0;
        int prod = 1;
        int index = -1;

        while (i > 0) {
            int bit = i & 1;
            i /= 2;
            index++;
            if (!bit) continue;

            count++;
            prod *= need[index];
        }

        ans += (count % 2) ? -n / prod : n / prod;
    }

    std::cout << ans;
}