#include <iostream>
#include <vector>

bool validate(std::vector<int>& containers, std::vector<int>& boxes, int amount) {
    int c = 0;
    int b = 0;

    while (b < boxes.size() && c < containers.size() && b < amount) {
        if (containers[c] >= 1 << boxes[b]) {
            b++;
        }

        c++;
    }

    return b == amount;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    std::vector<int> b(m);

    int left = 0;
    int right = m;

    while (left <= right) {
        int middle = (left + right) / 2;

        if (validate(a, b, middle)) {
            left = middle + 1;
        }

        else {
            right = middle - 1;
        }
    }

    std::cout << right << std::endl;
}