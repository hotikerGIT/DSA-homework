#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

bool pred(int num, int x, int y) {
    return x <= num && num <= y;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    int bucket_size = 317;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    // sqrt(е5) бакетов размером sqrt(е5), все числа в бакетах отсортированны
    std::vector<std::vector<int>> sorted_a;
    for (int i = 0; i < n; i += bucket_size) {
        int end = std::min(i + bucket_size, n);
        std::vector<int> bucket(a.begin() + i, a.begin() + end);
        std::sort(bucket.begin(), bucket.end());
        sorted_a.push_back(bucket);
    }

    for (int i = 0; i < q; ++i) {
        int l, r, x, y;
        std::cin >> l >> r >> x >> y;
        --l;
        --r;

        int res = 0;

        int left_bucket_index = l / bucket_size;
        int right_bucket_index = r / bucket_size;

        // считаем невошедшие края
        for (int j = l; j <= std::min(r, (left_bucket_index + 1) * bucket_size - 1) && j < n; ++j) {
            if (pred(a[j], x, y)) res++;
        }

        if (left_bucket_index < right_bucket_index) {
            for (int j = std::max(l, right_bucket_index * bucket_size); j <= r && j < n; ++j) {
                if (pred(a[j], x, y)) res++;
            }
        }

        for (int j = left_bucket_index + 1; j < right_bucket_index && j < sorted_a.size(); ++j) {
            auto& cur_bucket = sorted_a[j];
            int left = std::lower_bound(cur_bucket.begin(), cur_bucket.end(), x) - cur_bucket.begin();
            int right = std::upper_bound(cur_bucket.begin(), cur_bucket.end(), y) - cur_bucket.begin();

            res += std::max(right - left, 0LL);
        }

        std::cout << res << std::endl;
    }
}