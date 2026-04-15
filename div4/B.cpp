#include <iostream>
#include <vector>

int main() {
    int t, n;
    std::cin >> t;

    while (t--) {
        std::cin >> n;
        std::vector<int> counter1(26, 0);
        std::vector<int> counter2(26, 0);

        char c;
        for (int i = 0; i < n; ++i) {
            std::cin >> c;
            counter1[c - 'a']++;
        }

        for (int i = 0; i < n; ++i) {
            std::cin >> c;
            counter2[c - 'a']++;
        }

        if (counter1 == counter2) {
            std::cout <<"YES\n";
        }

        else {
            std::cout << "NO\n";
        }
    }
}