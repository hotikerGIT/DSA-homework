#include <iostream>

int main() {
    int xa, ya, xb, yb, xc, yc;
    std::cin >> xa >> ya >> xb >> yb >> xc >> yc;

    std::cout << 3 << '\n';
    std::cout << xa + xb - xc << ' ' << ya + yb - yc << '\n';
    std::cout << xa + xc - xb << ' ' << ya + yc - yb << '\n';
    std::cout << xc + xb - xa << ' ' << yc + yb - ya << '\n';
}