#include <iostream>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int x, y, z;
        std::cin >> x >> y >> z;
        std::string res;
        char c;

        if (x >= y && x >= z) {
            c = 'P';
        } else if (y >= x && y >= z) {
            c = 'R';
        } else {
            c = 'S';
        }

        for (int i = 0; i < x + y + z; ++i) res += c;

        std::cout << res << std::endl;
    }
}