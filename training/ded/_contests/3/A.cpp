#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> bits;

    while (n > 0) {
        bits.push_back(n & 1);
        n >>= 1;
    }

    std::reverse(bits.begin(), bits.end());
    int p = 1;
    int q = 1;

    for (int i = 1; i < bits.size(); ++i) {
        int bit = bits[i];

        if (bit == 0) {
            q += p;
        }

        else {
            p += q;
        }
    }

    std::cout << p << '/' << q;
}