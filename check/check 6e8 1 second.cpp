#include <iostream>
#include <chrono>

int main() {
    long long total = 0;
    int n = 30; // 2^30 чисел (гипотетически)

    auto start = std::chrono::high_resolution_clock::now();

    // Пример: 600M битовых операций
    for (long long i = 0; i < 600000000LL; i++) {
        total++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time: " << duration.count() << " ms, total: " << total << std::endl;
    return 0;
}