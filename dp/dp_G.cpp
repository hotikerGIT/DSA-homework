#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::string input;
    std::cin >> input;
    std::vector<int> digits = {0, 0};
    int size = input.length() + 2;

    for (char digit : input) {
        digits.push_back(digit - 48);
    }

    bool flag = false;
    for (int i = size - 1; i >= 2; --i) {
        if (digits[i] % 2 != 0) {
            continue;
        }

        for (int j = i - 1; j >= 1; --j) {
            for (int k = j - 1; k >= 0; --k) {
                if ((4 * digits[k] + 2 * digits[j] + digits[i]) % 8 == 0) {
                    flag = true;
                    std::cout << "YES" << std::endl;
                    std::cout << digits[k] * 100 + digits[j] * 10 + digits[i];
                    break;
                }
            }

            if (flag) {
                break;
            }
        }

        if (flag) {
            break;
        }
    }

    if (!flag) {
        std::cout << "NO";
    }

    return 0;
}