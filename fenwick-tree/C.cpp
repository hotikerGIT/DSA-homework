#include <iostream>
#include <vector>

long long merge(std::vector<int>& vec, std::vector<int>& temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    long long res = 0;

    while (i <= mid && j <= right) {
        if (vec[i] <= vec[j]) temp[k++] = vec[i++];
        else {
            temp[k++] = vec[j++];
            res += mid - i + 1;
        }
    }

    while (i <= mid) temp[k++] = vec[i++];
    while (j <= right) temp[k++] = vec[j++];

    for (i = left; i <= right; i++) vec[i] = temp[i];

    return res;
}

long long merge_sort(std::vector<int>& vec, std::vector<int>& temp, int left, int right) {
    if (left >= right) return 0;

    int mid = (right + left) / 2;
    long long res = 0;

    res += merge_sort(vec, temp, left, mid);
    res += merge_sort(vec, temp, mid + 1, right);
    res += merge(vec, temp, left, mid, right);

    return res;
}

int main() {
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> temp(n);

    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::cout << merge_sort(a, temp, 0, n - 1) << '\n';

    return 0;
}