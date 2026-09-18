#include <iostream>
#include <vector>
#include <string>

int main() {
    int x;
    std::cin >> x;

    std::string res;

    for (int i = 0; i < 25; ++i) {
        res += "AR";
    }

    for (int i = 0; i < 23; ++i) {
        res += "CR";
    }

    res += "C";

    for (int i = 0; i < 600 - x; ++i) {
        res.replace(res.find("ARC"), 3, "CRA");
    }

    std::cout << res;
}