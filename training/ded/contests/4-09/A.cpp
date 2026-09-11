#include <iostream>
#include <vector>

int main() {
    int n;
    char L, M, R;
    std::cin >> n >> L >> M >> R;
    int left = 0, right = 2;

    for (int i = 0; i < n - 1; ++i) {
        std::cin >> L >> M >> R;
        std::string res = "DD";
        bool is_left_occupied = false;
        bool is_right_occupied = false;

        if (L == 'C') {
            is_left_occupied = true;

            res[0] = left == 0 ? 'D' : 'L';
            left = 0;
        }

        if (R == 'C') {
            is_right_occupied = true;
            res[1] = right == 2 ? 'D' : 'R';
            right = 2;
        }

        if (M == 'C') {
            if (!is_left_occupied) {
                res[0] = left == 1 ? 'D' : 'R';
                left = 1;

                if (!is_right_occupied) {
                    res[1] = right == 2 ? 'D' : 'R';
                    right = 2;
                }
            }

            else {
                res[1] = right == 1 ? 'D' : 'L';
                right = 1;
            }
        }

        std::cout << res << '\n';
    }
}