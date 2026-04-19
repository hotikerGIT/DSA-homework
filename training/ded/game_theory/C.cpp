#include <iostream>
using namespace std;

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        long long N, K;
        cin >> N >> K;

        if (K % 3 != 0) {
            cout << (N % 3 != 0 ? "Alice" : "Bob") << endl;
        } else {
            long long period = K + 1;
            N %= period;
            if (N == 0) cout << "Bob" << endl;
            else if (N == K) cout << "Alice" << endl;
            else {
                cout << (N % 3 != 0 ? "Alice" : "Bob") << endl;
            }
        }
    }


    return 0;
}