#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    // T[n][k] = число разбиений n строк на k классов размера >= 2
    vector<vector<long long>> T(n + 1, vector<long long>(n + 1, 0));
    T[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            T[i][j] += T[i-1][j] * j;

            if (i >= 2) {
                T[i][j] += T[i-2][j-1] * (i-1);
            }
        }
    }

    long long ans = 0;
    for (int k = 1; k <= n/2; k++) {
        ans += T[n][k];
    }

    cout << ans << endl;

    return 0;
}