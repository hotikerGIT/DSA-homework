#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> func(vector<unsigned long long>& masks, int n, int m, int bit_count) {
    string bitmask(bit_count, '1');
    bitmask.resize(n, '0');

    unsigned long long full_mask = (1ULL << m) - 1;

    do {
        unsigned long long coverage = 0;
        vector<int> update;
        update.reserve(bit_count);

        for (int i = 0; i < n; ++i) {
            if (bitmask[i] == '1') {
                coverage |= masks[i];
                update.push_back(i + 1);

                // Быстрая проверка: если уже покрыли всё, можно не продолжать
                if (coverage == full_mask) {
                    return update;
                }
            }
        }

        if (coverage == full_mask) {
            return update;
        }
    } while (prev_permutation(bitmask.begin(), bitmask.end()));

    return {};
}

int main() {
    ifstream file_input("input.txt");
    ofstream file_output("output.txt");

    int n, m;
    file_input >> n >> m;

    // Преобразуем в битовые маски
    vector<unsigned long long> masks(n, 0);
    for (int i = 0; i < n; ++i) {
        int tests;
        file_input >> tests;
        for (int j = 0; j < tests; ++j) {
            int test;
            file_input >> test;
            masks[i] |= (1ULL << (test - 1));
        }
    }

    int left = 1;
    int right = n;
    vector<int> out;
    while (left <= right) {
        int middle = (left + right) / 2;

        std::vector<int> tmp = func(masks, n, m, middle);
        if (!tmp.empty()) {
            out = tmp;
            right = middle - 1;
        }

        else {
            left = middle + 1;
        }
    }

    file_output << out.size() << std::endl;
    for (int num : out) {
        file_output << num << " ";
    }
}