#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long
using namespace __gnu_pbds;
typedef tree<int, null_type, std::less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    ordered_set suffix, prefix;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        suffix.insert(a[i]);
    }

    int ans = 0;
    for (int middle = 0; middle < n; ++middle) {
        suffix.erase(a[middle]);
        ans += (middle - prefix.order_of_key(a[middle])) * suffix.order_of_key(a[middle]);
        prefix.insert(a[middle]);
    }

    std::cout << ans;
}