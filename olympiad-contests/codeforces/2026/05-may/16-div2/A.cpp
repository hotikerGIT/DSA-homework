#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(4);
        for (int i = 0; i < n; ++i) {
            int num;
            std::cin >> num;
            a[num]++;
        }

        int ans = a[0];
        int one_two_count = std::min(a[1], a[2]);
        ans += one_two_count;
        a[1] -= one_two_count;
        a[2] -= one_two_count;
        ans += a[1] / 3;
        ans += a[2] / 3;

        std::cout << ans << '\n';
    }
}
