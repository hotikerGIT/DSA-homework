#include <string>
#include <vector>
#include <iostream>

int main() {
    int k;
    std::string s;
    std::cin >> k >> s;

    std::vector<int> primes;
    for (int i = 2; i <= (int)s.size(); ++i) {
        bool flag = true;

        for (int p : primes) {
            if (i % p == 0) {
                flag = false;
                break;
            }
        }

        if (flag) {
            primes.push_back(i);
        }
    }

    for (int i = 0; i < k; ++i) {
        std::string prev((int)s.size(), '-');

        for (int j = 0; j < primes.size(); ++j) {
            prev[primes[j] - 1] = s[j];
        }

        int index = (int)primes.size();
        for (int j = 0; j < s.size(); ++j) {
            if (prev[j] != '-') continue;

            prev[j] = s[index];
            index++;
        }

        s = prev;
    }

    std::cout << s;
}