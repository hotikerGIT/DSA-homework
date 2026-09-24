#include <iostream>
#define int long long

signed main() {
    int n;
    std::cin >> n;

    int one = 0;
    int ten = 0;
    int hundred = 0;

    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;

        int change = (a / 1000 + (1 - (a % 1000 == 0))) * 1000 - a;
        one += change % 10;
        ten += (change % 100) / 10;
        hundred += (change % 1000) / 100;
    }

    std::cout << one << ' ' << ten << ' ' << hundred;
}