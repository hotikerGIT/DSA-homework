#include <iostream>
#include <string>

int main() {
    std::string num;
    std::cin >> num;

    bool is_first_q = num[0] == '?';
    int digit_sum = 0;
    int last_q = -1;
    int q_count = 0;

    for (int i = 0; i < num.size(); ++i) {
        char c = num[i];

        if (c != '?') digit_sum += c - '0';
        if (c == '?') {
            q_count++;
            last_q = i;
        }
    }

    int req = (3 - (digit_sum % 3)) % 3;

    std::string res;

    for (int i = 0; i < num.size(); ++i) {
        char c = num[i];

        if (c != '?') {
            res += c;
            continue;
        }

        if (i == 0) {
            if (q_count == 1) {
                if (req == 0 && num.size() > 1) {
                    req = 3;
                }
                res += (char)('0' + req);
            } else {
                res += '1';
            }
            continue;
        }

        if (i == last_q) {
            res += (char)('0' + (3 + req - is_first_q) % 3);
            continue;
        }

        res += '0';
    }

    if (last_q == -1 && std::stoi(num) % 3 != 0) {
        std::cout << -1;
    } else {
        std::cout << res;
    }
}