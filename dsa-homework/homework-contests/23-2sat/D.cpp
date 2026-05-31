#include <iostream>
#include <vector>
#include <functional>
#include <set>

struct Edge {
    int to, id;

    bool operator<(const Edge& other) const {
        return id < other.id;
    }
};

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> counter(n + 1);
    std::vector<std::vector<int>> matrix(2, std::vector<int>(n));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
            counter[matrix[i][j]]++;
        }
    }

    for (int num = 1; num <= n; ++num) {
        if (counter[num] != 2) {
            std::cout << -1 << '\n';
            return;
        }
    }

    std::vector<std::set<Edge>> graph(n + 1);
    std::vector<std::vector<Edge>> ass_graph(n + 1);
    for (int i = 0; i < n; ++i) {
        graph[matrix[0][i]].emplace(matrix[1][i], i);
        ass_graph[matrix[0][i]].emplace_back(matrix[1][i], i);
        ass_graph[matrix[1][i]].emplace_back(matrix[0][i], i);
    }

    std::vector<int> visited(n + 1);
    int res = 0;
    std::vector<int> out;

    std::function<void(int, int, int, std::vector<int>&, std::vector<int>&)> dfs = [&](
        int cur, int prev_id, int target,
        std::vector<int>& tr1, std::vector<int>& tr2)
    {
        visited[cur] = true;
        if (cur == target) return;

        for (const auto& next : ass_graph[cur]) {
            if (next.id == prev_id) continue;

            if (!graph[cur].contains(next)) {
                tr1.push_back(next.id);
            } else {
                tr2.push_back(next.id);
            }

            dfs(next.to, next.id, target, tr1, tr2);
        }
    };

    for (int v = 1; v <= n; ++v) {
        if (visited[v]) continue;
        std::vector<int> tr1, tr2;
        auto edge = *ass_graph[v].begin();
        if (!graph[v].contains(edge)) {
            tr1.push_back(edge.id);
        } else {
            tr2.push_back(edge.id);
        }
        dfs(edge.to, edge.id, v, tr1, tr2);

        if (tr1.size() > tr2.size()) std::swap(tr1, tr2);
        res += tr1.size();

        for (int id : tr1) {
            out.push_back(id + 1);
        }
    }

    std::cout << res << '\n';
    for (int id : out) {
        std::cout << id << ' ';
    }
    std::cout << '\n';
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}