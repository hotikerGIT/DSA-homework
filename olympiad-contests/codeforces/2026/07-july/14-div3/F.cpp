#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

std::vector<std::vector<int>> graph;
std::vector<int> order;
std::vector<int> start, end;
bool answer = true;

bool isCyclicShift(const std::vector<int>& A, const std::vector<int>& B) {
    int n = A.size();

    for (int st = 0; st < n; ++st) {
        if (A[st] != B[0]) continue;

        bool ok = true;
        for (int j = 0; j < n; ++j) {
            if (B[j] != A[(st + j) % n]) {
                ok = false;
                break;
            }
        }

        if (ok) return true;
    }
    return false;
}

void dfs(int cur, int prev) {
    bool is_leaf = true;
    for (int next : graph[cur]) {
        if (next != prev) {
            is_leaf = false;
            dfs(next, cur);
        }
    }
    if (is_leaf) return;

    std::set<std::pair<int, int>> intervals;
    for (int next : graph[cur]) {
        if (next != prev) intervals.emplace(start[next], end[next]);
    }

    bool flag_continuous = true;
    int pr = intervals.begin()->first - 1;
    for (const auto & interval : intervals) {
        if (pr != interval.first - 1) flag_continuous = false;
        pr = interval.second;
    }

    bool flag_increasing = true;
    std::vector<int> numbers, copy;
    for (int next : graph[cur]) {
        if (next != prev) {
            numbers.push_back(start[next]);
            copy.push_back(start[next]);
        }
    }
    std::sort(copy.begin(), copy.end());

    flag_increasing = isCyclicShift(numbers, copy);

    if (flag_increasing && flag_continuous) {
        start[cur] = intervals.begin()->first;
        end[cur] = (--intervals.end())->second;
    } else {
        start[cur] = -1;
        end[cur] = -1;
        answer = false;
    }
}

void solve() {
    int n;
    std::cin >> n;

    graph.clear();
    order.clear();
    start.clear();
    end.clear();

    graph.resize(n + 1);
    order.resize(n + 1);
    start.resize(n + 1);
    end.resize(n + 1);

    for (int i = 2; i <= n; ++i) {
        int p;
        std::cin >> p;

        graph[i].push_back(p);
        graph[p].push_back(i);
    }

    for (int i = 1; i <= n; ++i) {
        std::cin >> order[i];

        if (order[i] != 0) {
            start[i] = order[i];
            end[i] = order[i];
        }
    }

    answer = true;
    dfs(1, 0);
    std::cout << (answer ? "YES\n" : "NO\n");
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}