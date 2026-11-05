#include <iostream>
#include <vector>
#include <map>
#include <queue>

struct Node {
    int i, j, day;
};

void solve() {
    int n;
    std::cin >> n;
    std::vector matrix(n, std::vector<std::vector<Node>>(7));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (i % 2 == 0 ? 6 : 7); ++j) {
            int num;
            std::cin >> num;
            std::vector<int> days(8, 1);

            while (num > 0) {
                int d = num % 10;
                num /= 10;
                days[d] = 0;
            }

            for (int d = 1; d < 8; ++d) {
                if (days[d]) {
                    matrix[i][j].push_back(Node(i, j, d));
                }
            }
        }
    }

    std::queue<std::vector<int>> q;
    q.emplace(0, 0, 1, 0, 0);
    std::vector visited(n, std::vector<int>(7, -1));
    while (!q.empty()) {
        auto data = q.front();
        q.pop();

        int i = data[0];
        int j = data[1];
        int day = data[2];
        int dist = data[3];
        int back = data[4];
        if (visited[i][j]) continue;
        if (back == 7) continue;
        visited[i][j] = 0;
        int next_day = (day + 1) % 7 + 1;

        if (i != 0) {
            q.emplace(i - 1, j, next_day, dist + 1, back + 1);
        }

        if (i != n - 1) {
            q.emplace(i + 1, j, next_day, dist + 1, back);
        }

        if (j != 0) {
            q.emplace(i, j - 1, next_day, dist + 1, back);
        }

        if (j + 1 != (i % 2 == 0 ? 6 : 7)) {
            q.emplace(i, j + 1, next_day, dist + 1, back);
        }
    }

    std::cout << visited.back()[(n % 2 == 0 ? 6 : 7) - 1] << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}