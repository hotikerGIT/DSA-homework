#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> rgb(3);
    for (int i = 0; i < 3; ++i) {
        std::cin >> rgb[i];
    }
    std::sort(rgb.begin(), rgb.end());

    int a = rgb[0];
    int g = rgb[1] - a;
    int b = rgb[2] - a;

    int res = a + g / 3 + b / 3;

    if (a != 0 && g % 3 == 2 && b % 3 == 2) {
        res++;
    }

    std::cout << res;
}