#include <functional>
#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long
using namespace __gnu_pbds;
using namespace std;
template<class T> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag,
        tree_order_statistics_node_update>;

signed main() {
    int x;
    std::cin >> x;
    ordered_set<int> set;
    set.insert(x);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        std::cin >> a >> b;

        set.insert(a);
        set.insert(b);

        std::cout << *set.find_by_order(i + 1) << '\n';
    }
}