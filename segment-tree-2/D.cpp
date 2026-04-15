#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

#define int long long

struct Item {
    int pos, value;

    bool operator<(const Item& other) const {
        if (pos != other.pos) return pos < other.pos;
        return value < other.value;
    }
};

class Fenwick {
private:
    std::vector<int> tree;
    int n;

public:
    Fenwick(int size) : n(size), tree(size, 0) {}

    void add(int pos, int delta = 1) {
        for (int i = pos; i < n; i |= i + 1) {
            tree[i] += delta;
        }
    }

    int sum(int r) {
        int result = 0;
        for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
            result += tree[i];
        }
        return result;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

void compress(std::vector<int>& arr) {
    std::set<int> unique;
    for (int x : arr) unique.insert(x);

    std::map<int, int> mapping;
    for (int x : unique) mapping[x] = mapping.size();
    for (int& x : arr) x = mapping[x];
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    std::map<int, int> val_at_pos;
    for (int i = 0; i < q; ++i) {
        int pos1, pos2;
        std::cin >> pos1 >> pos2;
        --pos1; --pos2;

        int val1 = val_at_pos.contains(pos1) ? val_at_pos[pos1] : pos1;
        int val2 = val_at_pos.contains(pos2) ? val_at_pos[pos2] : pos2;

        val_at_pos[pos1] = val2;
        val_at_pos[pos2] = val1;
    }

    std::vector<Item> a;
    a.reserve(val_at_pos.size());
    for (const auto& [pos, val] : val_at_pos) a.push_back({pos, val});

    int n = a.size();
    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = a[i].value;
    }
    compress(b);

    Fenwick T(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += T.sum(b[i], n - 1);
        T.add(b[i]);
    }

    std::sort(a.begin(), a.end());

    for (int after_idx = 0; after_idx < n; ++after_idx) {
        Item search = {a[after_idx].value, -1};
        int before_idx = std::lower_bound(a.begin(), a.end(), search) - a.begin();

        ans += std::abs(a[after_idx].pos - a[before_idx].pos);
        ans -= std::abs(after_idx - before_idx);
    }

    std::cout << ans << std::endl;

    return 0;
}