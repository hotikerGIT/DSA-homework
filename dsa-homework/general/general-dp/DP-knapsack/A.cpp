#include <iostream>
#include <vector>

int main() {
    int t, n;
    long long w;
    std::cin >> t;

    while (t--) {
        std::cin >> n >> w;
        std::vector<long long> weights(n);
        std::vector<int> res;

        for (int i = 0; i < n; ++i) {
            std::cin >> weights[i];
        }

        long long prev = 0;
        long long want = (w + 1) / 2;

        for (int i = 0; i < n; ++i) {
            if (weights[i] > w) { continue; }
            if (weights[i] >= want) {
                prev = weights[i];
                res = {i};
                break;
            }

            prev += weights[i];
            res.push_back(i);

            if (prev >= want) {
                break;
            }
        }

        if (prev >= want) {
            std::cout << res.size() << std::endl;

            for (int num : res) {
                std::cout << num + 1 << " ";
            }
        }

        else {
            std::cout << -1;
        }

        std::cout << std::endl;
    }
}