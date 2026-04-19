#include <iostream>
#include <vector>
#define int long long

int ans = 0;
int n, b;
std::vector<std::vector<std::pair<int, int>>> projects;

void rec(int cur_project, int cur_sum, int cur_cost) {
    if (cur_project == n) {
        ans = std::max(ans, cur_cost <= b ? cur_sum : 0);
        return;
    }

    auto& project = projects[cur_project];
    for (auto& [value, cost] : project) {
        rec(cur_project + 1, cur_sum + value, cur_cost + cost);
    }
}

signed main() {
    std::cin >> n >> b;
    projects.resize(n);
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        projects[i].resize(k + 1);

        for (int j = 0; j < k; ++j) {
            int r, e;
            std::cin >> r >> e;
            projects[i][j] = {r, e};
        }
    }

    rec(0, 0, 0);
    std::cout << ans;
}