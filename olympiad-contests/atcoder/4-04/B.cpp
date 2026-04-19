#include <iostream>
#include <vector>

int main() {
    int h, w;
    std::cin >> h >> w;
    for (int i = 0; i < w; ++i) {
        std::cout << '#';
    }
    std::cout << '\n';

    for (int i = 0; i < h - 2; ++i) {
        for (int j = 0; j < w; ++j) {
            if (j == 0 or j == w - 1) std::cout << '#';
            else std::cout << '.';
        }
        std::cout << '\n';
    }

    for (int i = 0; i < w; ++i) {
        std::cout << '#';
    }
    std::cout << '\n';
}