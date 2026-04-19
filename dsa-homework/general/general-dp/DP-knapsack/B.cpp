#include <iostream>
#include <vector>
#include <cmath>

long long recursion(std::vector<long long>& counts,  // здесь для того чтобы понять можно ли взять конкретный margin
                    std::vector<long long>& dp,  // здесь за тем же зачем и counts
                    std::vector<int>& used,  // здесь для того чтобы понять, когда выходить из рекурсии
                    long long w,  // цель по весу
                    long long cur_w,  // текущий вес
                    int cur_num) {  // текущий элемент который выбирается
    long long result = 0;

    if (used[cur_num] == 8 || cur_num == 0) {
        // как только текущий элемент был взят слишком много раз
        // прекращаем рекурсию
        return (cur_w <= w) ? cur_w : 0;
    }

    if (cur_w <= w) {
        result = cur_w;

        // описываем рекурсивный бэктрекинг для взятия веса
        // если можем взять элемент
        if (counts[cur_num]) {
            // изображаем взятие элемента
            dp[cur_num]++;
            counts[cur_num]--;

            // запускаем рекурсию и обновляем результат
            result = std::max(result, recursion(counts, dp, used, w, cur_w + cur_num, cur_num));

            // возвращаем элемент
            dp[cur_num]--;
            counts[cur_num]++;
        }

        else {
            // если элемента нет, переходим к следующему
            result = std::max(result, recursion(counts, dp, used, w, cur_w, cur_num - 1));
        }

        return result;  // возвращаем полученное значение
        // также важно отметить что мы пройдемся с уменьшением взятого числа все равно
        // но только когда войдем в рекурсию в этом условии
        // и не войдем в это условие в следующем шаге рекурсии
    }

    // описываем рекурсию при переборе

    // сначала определяем минимальную разницу (cur_w - w)
    int margin = cur_w - w;

    // пытаемся ее взять
    // для каждой возможной разницы обойдем dp в поисках возможности взять разницу
    bool flag = false;
    for (int i = margin; i <= 8 && !flag; ++i) {
        for (int j = 8; j - margin >= 0; --j) {
            // если получилось взять такую разницу
            // то есть есть хотя бы один элемент в dp и в counts
            // так как dp отвечает за взятые а counts за оставшиеся
            if (dp[j] && counts[j - margin]) {
                // обновляем ответ и выходим из цикла
                flag = true;
                result = cur_w - margin;

                break;
            }
        }
    }

    // далее итерируемся от 1 до 8, пытаясь убрать i текущих элементов
    for (int neg_el = 0; neg_el <= 8; neg_el++) {
        // для каждой итерации запускаем рекурсию, в которой все обыщится снова

        dp[cur_num] -= neg_el;
        counts[cur_num] += neg_el;
        used[cur_num] += neg_el;

        if (dp[cur_num] < 0) {
            flag = true;
        }

        else {
            result = std::max(result, recursion(counts, dp, used, w, cur_w - cur_num * neg_el, cur_num - 1));
        }

        dp[cur_num] += neg_el;
        counts[cur_num] -= neg_el;
        used[cur_num] -= neg_el;

        if (flag) {
            break;
        }
    }

    return result; // возвращаем лучший возможный результат без перебора
}

int main() {
    long long w;
    std::cin >> w;

    long long sum = 0;
    std::vector<long long> counts(9);
    for (int i = 1; i < 9; ++i) {
        std::cin >> counts[i];
        sum += i * counts[i];
    }
    counts[0] = 1000;

    if (sum <= w) {
        std::cout << sum;
        return 0;
    }

    std::vector<long long> dp(9);
    int cur = 8;
    long long temp = w;

    std::vector<int> used(9, 0);  // сколько использовано

    // берем веса которые можем (с перебором)
    while (temp > 0) {
        dp[cur] = std::min(counts[cur], (temp + cur - 1) / cur);
        temp -= dp[cur] * cur;
        counts[cur] -= dp[cur];
        cur--;
    }

    /*for (int num : dp) {
        std::cout << num << " ";
    }*/

    std::cout << recursion(counts, dp, used, w, w - temp, 8);
}