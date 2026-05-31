#include <iostream>
#include <iomanip>

int main() {
    double a, b, c, d;
    std::cin >> a >> b >> c >> d;
    double win = a / b;
    double good_miss = 1 - c / d;
    double bad_miss = 1 - a / b;

    double res = 0;
    double prev_good_miss = 1;
    double prev_bad_miss = 1;

    for (int i = 0; i < 1e6; ++i) {
        res += prev_bad_miss * prev_good_miss * win;
        prev_bad_miss *= bad_miss;
        prev_good_miss *= good_miss;
    }

    std::cout << std::fixed << std::setprecision(6) << res;
}