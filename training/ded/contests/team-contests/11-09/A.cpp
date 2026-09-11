#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;


    for (int side = 100; side >= 0; side -= 2) {
        if (a >= side * side / 2 && b >= side * side / 2) {
            std::cout << side;
            return 0;
        }
    }
}