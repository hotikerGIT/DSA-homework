#include <vector>
#include <algorithm>
#include <iostream>
#define int long long

std::vector<int> process;
std::vector<std::vector<std::pair<int, int>>> global_map;
const int BLOCK_SIZE = 450;
const int MOD = 1e9 + 7;

int ans = 1;
int minus_val = 1;
int plus_val = 1;
const int N = 1e7 + 5;
int lp[N] = {0};
std::vector<int> primes;

int mod_pow(int a, int n) {
    int res = 1;
    for (; n != 0; n >>= 1, a = (a * 1LL * a) % MOD) {
        if (n & 1) res = (res * 1LL * a) % MOD;
    }
    return res;
}

void lp_fill() {
    for (int i = 2; i < N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > lp[i] || 1LL * i * p >= N) break;
            lp[i * p] = p;
        }
    }
}

void get_dividers(std::vector<std::pair<int, int>>& vec, int a) {
    vec.clear();
    while (a > 1) {
        int p = lp[a];
        int cnt = 0;
        while (a % p == 0) {
            a /= p;
            cnt++;
        }
        vec.emplace_back(p, cnt);
    }
}

void GetGlobalMap(std::vector<int>& vec) {
    global_map.reserve(N);
    std::vector<std::pair<int, int>> temp;
    for (int num : vec) {
        if (!global_map[num].empty()) continue;
        get_dividers(temp, num);
        global_map[num] = temp;
    }
}

struct Query {
    int l, r, idx;
    Query(int _l, int _r, int _idx) : l(_l), r(_r), idx(_idx) {}

    bool operator<(const Query& other) const {
        if (l / BLOCK_SIZE != other.l / BLOCK_SIZE)
            return l < other.l;
        return r < other.r;
    }
};

void add(int number) {
    for (auto& [num, count] : global_map[number]) {
        minus_val = (minus_val * (process[num] + 1)) % MOD;
        process[num] += count;
        plus_val = (plus_val * (process[num] + 1)) % MOD;
    }
}

void remove(int number) {
    for (auto& [num, count] : global_map[number]) {
        minus_val = (minus_val * (process[num] + 1)) % MOD;
        process[num] -= count;
        plus_val = (plus_val * (process[num] + 1)) % MOD;
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    lp_fill();
    GetGlobalMap(a);
    process.resize(N, 0);

    std::vector<Query> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        queries.emplace_back(l - 1, r - 1, i);
    }

    std::sort(queries.begin(), queries.end());
    std::vector<int> answers(q);

    int cur_l = 0, cur_r = -1;
    ans = 1;

    for (auto& query : queries) {
        minus_val = 1;
        plus_val = 1;

        while (cur_r < query.r) {
            ++cur_r;
            add(a[cur_r]);
        }
        while (cur_r > query.r) {
            remove(a[cur_r]);
            --cur_r;
        }
        while (cur_l < query.l) {
            remove(a[cur_l]);
            ++cur_l;
        }
        while (cur_l > query.l) {
            --cur_l;
            add(a[cur_l]);
        }

        ans = (ans * mod_pow(minus_val, MOD - 2)) % MOD;
        ans = (ans * plus_val) % MOD;
        answers[query.idx] = ans;
    }

    for (int num : answers) std::cout << num << '\n';
}