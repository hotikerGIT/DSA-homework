#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> perfect_squares;
    for (int i = 1; i * i < 3 * n; i += 2) {
        perfect_squares.push_back(i * i);
    }

    std::cout << 0 << ' ';
    for (int sq : perfect_squares) {
        if ((sq - 1) % (4 * n)) continue;

        int x = (1 + sq) / 2;
        std::cout << x << ' ';
    }
}