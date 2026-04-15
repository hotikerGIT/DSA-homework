#include <iostream>
#include <vector>

int main() {
    int N = 1e5;
    std::vector<char> dp(N + 5, false);
    std::vector<int> moves = {1, 5, 13};
    for (int i = 2; i < N; ++i) {
        for (int move : moves) {
            if (i > move) dp[i] |= !dp[i - move];
        }
    }

    int n;
    std::cin >> n;
    std::cout << (dp[n] ? 1 : 2);
}