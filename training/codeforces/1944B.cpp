#include <iostream>
#include <vector>

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(2 * n);
    for (int& num : a) std::cin >> num;

    std::vector<int> left, right;
    std::vector<int> has_left(n + 1), has_right(n + 1);
    for (int i = 0; i < n; ++i) has_left[a[i]] = 1;
    for (int i = n; i < 2 * n; ++i) has_right[a[i]] = 1;

    std::vector<int> visited(n + 1);
    for (int i = 0; i < n && left.size() < 2 * k; ++i) {
        if (visited[a[i]] || has_right[a[i]]) continue;

        left.push_back(a[i]);
        left.push_back(a[i]);
        visited[a[i]] = 1;
    }

    for (int i = n; i < 2 * n && right.size() < 2 * k; ++i) {
        if (has_left[a[i]] || visited[a[i]]) continue;

        right.push_back(a[i]);
        right.push_back(a[i]);
        visited[a[i]] = 1;
    }

    for (int i = 0; i < n && left.size() < 2 * k; ++i) {
        if (visited[a[i]]) continue;

        left.push_back(a[i]);
        right.push_back(a[i]);
    }

    for (int num : left) std::cout << num << ' ';
    std::cout << '\n';
    for (int num : right) std::cout << num << ' ';
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) solve();
}