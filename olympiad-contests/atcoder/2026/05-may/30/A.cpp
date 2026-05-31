#include <iostream>

int main() {
    int n, m;
    std::cin >> n >> m;

    int cnt = 0;
    int x = m;
    while (x > 0) {
        x = n % x;
        cnt++;
    }

    std::cout << cnt;
}