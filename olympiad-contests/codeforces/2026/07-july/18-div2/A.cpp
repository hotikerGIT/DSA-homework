#include <iostream>

int main() {
    int t;
    std::cin >> t;

    while(t--) {
        int n;
        std::cin >> n;
        int running_sum = 0;

        for (int i = 0; i < n; ++i) {
            int p;
            std::cin >> p;
            running_sum += p;
        }

        std::cout << (running_sum % 4 == 0 ? "YES\n" : "NO\n");
    }
}