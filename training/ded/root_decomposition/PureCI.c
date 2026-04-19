#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MOD 1000000007LL
#define BLOCK_SIZE 500
#define N 10000005

typedef long long ll;

typedef struct {
    int prime;
    int power;
} Factor;

typedef struct {
    Factor* factors;
    int count;
    int number;  // Храним исходное число для быстрого поиска
} Factorization;

typedef struct {
    int l;
    int r;
    int idx;
} Query;

// Глобальные структуры данных
ll ans = 1;
ll minus_val = 1;
ll plus_val = 1;

int lp[N];
int* primes = NULL;
int primes_count = 0;

Factorization* global_map = NULL;
int global_map_capacity = 0;
int global_map_size = 0;

ll* process_keys = NULL;
ll* process_values = NULL;
int process_size = 0;
int process_capacity = 0;

// Вспомогательные функции
ll mod_pow(ll a, ll n) {
    ll res = 1;
    a = a % MOD;
    while (n > 0) {
        if (n & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        n >>= 1;
    }
    return res;
}

// Инициализация решета Эратосфена
void lp_fill() {
    for (int i = 0; i < N; i++) lp[i] = 0;

    // Оценка количества простых чисел (приблизительно N/ln(N))
    int max_primes = N / 10 + 100;
    primes = (int*)malloc(max_primes * sizeof(int));
    if (!primes) exit(1);

    primes_count = 0;
    for (int i = 2; i < N; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes[primes_count++] = i;
        }
        for (int j = 0; j < primes_count; j++) {
            int p = primes[j];
            if (p > lp[i] || (ll)i * p >= N) break;
            lp[i * p] = p;
        }
    }
}

// Факторизация числа
Factorization get_dividers(int a) {
    Factorization result;
    result.number = a;
    result.factors = (Factor*)malloc(20 * sizeof(Factor)); // Максимум 20 различных простых делителей
    if (!result.factors) exit(1);
    result.count = 0;

    int temp = a;
    while (temp > 1) {
        int p = lp[temp];
        int cnt = 0;
        while (temp % p == 0) {
            temp /= p;
            cnt++;
        }
        result.factors[result.count].prime = p;
        result.factors[result.count].power = cnt;
        result.count++;
    }

    return result;
}

// Поиск факторизации в global_map
Factorization* find_factorization(int number) {
    for (int i = 0; i < global_map_size; i++) {
        if (global_map[i].number == number) {
            return &global_map[i];
        }
    }
    return NULL;
}

// Инициализация глобальной карты факторизаций
void init_global_map(int* arr, int n) {
    global_map_capacity = n;
    global_map = (Factorization*)malloc(global_map_capacity * sizeof(Factorization));
    if (!global_map) exit(1);
    global_map_size = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < global_map_size; j++) {
            if (global_map[j].number == arr[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (global_map_size >= global_map_capacity) {
                global_map_capacity *= 2;
                global_map = (Factorization*)realloc(global_map, global_map_capacity * sizeof(Factorization));
                if (!global_map) exit(1);
            }
            global_map[global_map_size++] = get_dividers(arr[i]);
        }
    }
}

// Бинарный поиск в process массиве
int find_process_index(int key) {
    for (int i = 0; i < process_size; i++) {
        if (process_keys[i] == key) return i;
    }
    return -1;
}

void ensure_process_capacity() {
    if (process_size >= process_capacity) {
        process_capacity = process_capacity == 0 ? 1000 : process_capacity * 2;
        process_keys = (ll*)realloc(process_keys, process_capacity * sizeof(ll));
        process_values = (ll*)realloc(process_values, process_capacity * sizeof(ll));
        if (!process_keys || !process_values) exit(1);
    }
}

// Добавление числа в текущий диапазон
void add(int number) {
    Factorization* factors = find_factorization(number);
    if (!factors) return;

    for (int i = 0; i < factors->count; i++) {
        int prime = factors->factors[i].prime;
        int power = factors->factors[i].power;

        int idx = find_process_index(prime);
        if (idx == -1) {
            ensure_process_capacity();
            idx = process_size;
            process_keys[process_size] = prime;
            process_values[process_size] = 0;
            process_size++;
        }

        minus_val = (minus_val * (process_values[idx] + 1)) % MOD;
        process_values[idx] += power;
        plus_val = (plus_val * (process_values[idx] + 1)) % MOD;
    }
}

// Удаление числа из текущего диапазона
void remove_number(int number) {
    Factorization* factors = find_factorization(number);
    if (!factors) return;

    for (int i = 0; i < factors->count; i++) {
        int prime = factors->factors[i].prime;
        int power = factors->factors[i].power;

        int idx = find_process_index(prime);
        if (idx == -1) continue;

        minus_val = (minus_val * (process_values[idx] + 1)) % MOD;
        process_values[idx] -= power;
        plus_val = (plus_val * (process_values[idx] + 1)) % MOD;
    }
}

// Функция сравнения для сортировки запросов
int compare_queries(const void* a, const void* b) {
    Query* q1 = (Query*)a;
    Query* q2 = (Query*)b;

    int block1 = q1->l / BLOCK_SIZE;
    int block2 = q2->l / BLOCK_SIZE;

    if (block1 != block2) {
        return (block1 < block2) ? -1 : 1;
    }

    // Для четных блоков сортируем по возрастанию r, для нечетных - по убыванию
    // (оптимизация для алгоритма Мо)
    if (block1 % 2 == 0) {
        return (q1->r < q2->r) ? -1 : (q1->r > q2->r);
    } else {
        return (q1->r > q2->r) ? -1 : (q1->r < q2->r);
    }
}

// Освобождение ресурсов
void cleanup() {
    if (primes) free(primes);
    if (process_keys) free(process_keys);
    if (process_values) free(process_values);

    if (global_map) {
        for (int i = 0; i < global_map_size; i++) {
            if (global_map[i].factors) free(global_map[i].factors);
        }
        free(global_map);
    }
}

int main() {
    // Установка обработчиков для корректного освобождения памяти
    atexit(cleanup);

    int n, q;
    if (scanf("%d %d", &n, &q) != 2) {
        fprintf(stderr, "Ошибка чтения n и q\n");
        return 1;
    }

    int* a = (int*)malloc(n * sizeof(int));
    if (!a) {
        fprintf(stderr, "Ошибка выделения памяти для массива a\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            fprintf(stderr, "Ошибка чтения элемента a[%d]\n", i);
            free(a);
            return 1;
        }
    }

    // Инициализация
    lp_fill();
    init_global_map(a, n);

    // Чтение запросов
    Query* queries = (Query*)malloc(q * sizeof(Query));
    if (!queries) {
        fprintf(stderr, "Ошибка выделения памяти для запросов\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        if (scanf("%d %d", &l, &r) != 2) {
            fprintf(stderr, "Ошибка чтения запроса %d\n", i);
            free(a);
            free(queries);
            return 1;
        }
        queries[i].l = l - 1;
        queries[i].r = r - 1;
        queries[i].idx = i;
    }

    // Сортировка запросов
    qsort(queries, q, sizeof(Query), compare_queries);

    // Массив ответов
    ll* answers = (ll*)malloc(q * sizeof(ll));
    if (!answers) {
        fprintf(stderr, "Ошибка выделения памяти для ответов\n");
        free(a);
        free(queries);
        return 1;
    }

    // Обработка запросов алгоритмом Мо
    int cur_l = 0, cur_r = -1;
    ans = 1;

    // Инициализация process массивов
    process_capacity = 1000;
    process_size = 0;
    process_keys = (ll*)malloc(process_capacity * sizeof(ll));
    process_values = (ll*)malloc(process_capacity * sizeof(ll));
    if (!process_keys || !process_values) {
        fprintf(stderr, "Ошибка выделения памяти для process\n");
        free(a);
        free(queries);
        free(answers);
        return 1;
    }

    for (int i = 0; i < q; i++) {
        Query query = queries[i];
        minus_val = 1;
        plus_val = 1;

        // Расширение/сужение диапазона
        while (cur_r < query.r) {
            cur_r++;
            add(a[cur_r]);
        }
        while (cur_r > query.r) {
            remove_number(a[cur_r]);
            cur_r--;
        }
        while (cur_l < query.l) {
            remove_number(a[cur_l]);
            cur_l++;
        }
        while (cur_l > query.l) {
            cur_l--;
            add(a[cur_l]);
        }

        // Обновление ответа
        ans = (ans * mod_pow(minus_val, MOD - 2)) % MOD;
        ans = (ans * plus_val) % MOD;
        answers[query.idx] = ans;
    }

    // Вывод результатов
    for (int i = 0; i < q; i++) {
        printf("%lld\n", answers[i]);
    }

    // Освобождение памяти (cleanup() сделает это автоматически)
    free(a);
    free(queries);
    free(answers);

    return 0;
}