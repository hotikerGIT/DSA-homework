#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;
const double EPS = 1e-9;

double solve_game(int n, vector<vector<double>>& p, int banned_a, int banned_t) {
    // n = N-1 (колод Такахаши после бана Аоки)
    // banned_t: какую B забанил Такахаши (0,1,2)
    // banned_a: какую A забанил Аоки (0..N-1)

    // Оставшиеся колоды Аоки
    vector<int> remaining_b;
    for (int j = 0; j < 3; j++) {
        if (j != banned_t) remaining_b.push_back(j);
    }

    // Если после бана у Аоки меньше 2 колод - такого не бывает, т.к. он банит 1 из 3

    // Оставшиеся колоды Такахаши
    vector<int> remaining_a;
    for (int i = 0; i < n+1; i++) { // n+1 = N
        if (i != banned_a) remaining_a.push_back(i);
    }

    int m = remaining_a.size(); // = N-1

    // Матрица игры m x 2
    vector<vector<double>> mat(m, vector<double>(2));
    for (int i = 0; i < m; i++) {
        mat[i][0] = p[remaining_a[i]][remaining_b[0]];
        mat[i][1] = p[remaining_a[i]][remaining_b[1]];
    }

    // Решаем игру m x 2
    // Ищем равновесие:
    // Такахаши максимизирует свой гарантированный выигрыш,
    // Аоки минимизирует

    // Для двух столбцов равновесие можно найти через ЛП:
    // Такахаши выбирает смесь alpha_i
    // Его выигрыш = min( sum alpha_i * mat[i][0], sum alpha_i * mat[i][1] )
    // Он хочет максимизировать это min

    // Это эквивалентно:
    // max t
    // s.t. sum alpha_i * mat[i][0] >= t
    //      sum alpha_i * mat[i][1] >= t
    //      sum alpha_i = 1, alpha_i >= 0

    // Решаем перебором опорных точек:
    // В равновесии alpha имеет не более 2 ненулевых компонент (т.к. 2 столбца у Аоки)

    double ans = 0;

    // Случай 1: чистая стратегия Такахаши
    for (int i = 0; i < m; i++) {
        ans = max(ans, min(mat[i][0], mat[i][1]));
    }

    // Случай 2: смесь из 2 строк
    for (int i1 = 0; i1 < m; i1++) {
        for (int i2 = i1+1; i2 < m; i2++) {
            // alpha * mat[i1][0] + (1-alpha) * mat[i2][0] =
            // alpha * mat[i1][1] + (1-alpha) * mat[i2][1] = t
            // Это даёт условие равенства двух столбцов для смеси:
            double a = mat[i1][0] - mat[i2][0] - mat[i1][1] + mat[i2][1];
            if (fabs(a) < EPS) continue; // параллельны, не дают равновесия

            double alpha = (mat[i2][1] - mat[i2][0]) / a;

            if (alpha >= -EPS && alpha <= 1+EPS) {
                alpha = max(0.0, min(1.0, alpha));
                double t = alpha * mat[i1][0] + (1-alpha) * mat[i2][0];
                // Проверим, что для всех строк t <= max...
                bool ok = true;
                for (int k = 0; k < m; k++) {
                    if (alpha * mat[i1][k%2?]...)
                    // Упрощённо: проверим, что смесь оптимальна
                    // В двухстолбцовой игре равновесная смесь alpha_i такова,
                    // что все строки дают <= t при игре Аокой против этой смеси
                    // и t достигается на i1,i2
                    // Это условие выполняется автоматически, если t - максимин
                }
                if (ok) ans = max(ans, t);
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    cout << fixed << setprecision(10);

    while (T--) {
        int N;
        cin >> N;

        vector<vector<double>> p(N, vector<double>(3));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 3; j++) {
                int x;
                cin >> x;
                p[i][j] = x / 1e6;
            }
        }

        // Матрица игры первого уровня: Такахаши выбирает b (0..2), Аоки выбирает a (0..N-1)
        vector<vector<double>> M(3, vector<double>(N));

        for (int b = 0; b < 3; b++) {
            for (int a = 0; a < N; a++) {
                M[b][a] = solve_game(N, p, a, b);
            }
        }

        // Решаем игру 3 x N
        // Такахаши максимизирует, Аоки минимизирует

        // Стратегия Такахаши: смесь по b
        // Стратегия Аоки: смесь по a

        // Ищем значение игры:
        // max_{q} min_{a} sum_b q_b * M[b][a]
        // где q_b >=0, sum q_b = 1

        double ans = 0;

        // Чистые стратегии Такахаши
        for (int b = 0; b < 3; b++) {
            double min_val = INF;
            for (int a = 0; a < N; a++) {
                min_val = min(min_val, M[b][a]);
            }
            ans = max(ans, min_val);
        }

        // Смеси из 2 стратегий Такахаши
        for (int b1 = 0; b1 < 3; b1++) {
            for (int b2 = b1+1; b2 < 3; b2++) {
                // Ищем alpha: alpha * M[b1][a] + (1-alpha) * M[b2][a] >= t для всех a
                // Максимизируем t
                // Это можно найти, перебирая пары a, где эти две строки пересекаются

                vector<double> points;
                points.push_back(0);
                points.push_back(1);

                for (int a1 = 0; a1 < N; a1++) {
                    for (int a2 = 0; a2 < N; a2++) {
                        double A = M[b1][a1] - M[b2][a1] - M[b1][a2] + M[b2][a2];
                        if (fabs(A) < EPS) continue;
                        double alpha = (M[b2][a2] - M[b2][a1]) / A;
                        if (alpha > -EPS && alpha < 1+EPS) {
                            points.push_back(alpha);
                        }
                    }
                }

                for (double alpha : points) {
                    alpha = max(0.0, min(1.0, alpha));
                    double t = INF;
                    for (int a = 0; a < N; a++) {
                        t = min(t, alpha * M[b1][a] + (1-alpha) * M[b2][a]);
                    }
                    ans = max(ans, t);
                }
            }
        }

        // Смесь из всех 3 стратегий Такахаши (полностью смешанная)
        // Перебираем тройки a, где они равны
        for (int a1 = 0; a1 < N; a1++) {
            for (int a2 = a1+1; a2 < N; a2++) {
                for (int a3 = a2+1; a3 < N; a3++) {
                    // Решаем систему:
                    // q0*M[0][a1] + q1*M[1][a1] + q2*M[2][a1] = t
                    // q0*M[0][a2] + q1*M[1][a2] + q2*M[2][a2] = t
                    // q0*M[0][a3] + q1*M[1][a3] + q2*M[2][a3] = t
                    // q0+q1+q2=1

                    vector<vector<double>> A(4, vector<double>(4, 0));
                    for (int r = 0; r < 3; r++) {
                        int aa = (r == 0 ? a1 : (r == 1 ? a2 : a3));
                        for (int c = 0; c < 3; c++) {
                            A[r][c] = M[c][aa];
                        }
                        A[r][3] = -1; // коэффициент при -t
                    }
                    A[3][0] = A[3][1] = A[3][2] = 1;
                    A[3][3] = 0;

                    // Правая часть
                    vector<double> b(4, 0);
                    b[3] = 1;

                    // Решаем методом Гаусса
                    vector<vector<double>> aug(4, vector<double>(5));
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            aug[i][j] = A[i][j];
                        }
                        aug[i][4] = b[i];
                    }

                    // Прямой ход
                    for (int col = 0; col < 4; col++) {
                        int pivot = col;
                        for (int row = col+1; row < 4; row++) {
                            if (fabs(aug[row][col]) > fabs(aug[pivot][col])) {
                                pivot = row;
                            }
                        }
                        swap(aug[col], aug[pivot]);

                        if (fabs(aug[col][col]) < EPS) continue;

                        double div = aug[col][col];
                        for (int j = col; j < 5; j++) {
                            aug[col][j] /= div;
                        }

                        for (int row = 0; row < 4; row++) {
                            if (row != col && fabs(aug[row][col]) > EPS) {
                                double factor = aug[row][col];
                                for (int j = col; j < 5; j++) {
                                    aug[row][j] -= factor * aug[col][j];
                                }
                            }
                        }
                    }

                    vector<double> sol(4, 0);
                    for (int i = 0; i < 4; i++) {
                        if (fabs(aug[i][i]) > EPS) {
                            sol[i] = aug[i][4];
                        }
                    }

                    double q0 = sol[0], q1 = sol[1], q2 = sol[2], t = -sol[3];

                    if (q0 >= -EPS && q1 >= -EPS && q2 >= -EPS &&
                        fabs(q0+q1+q2-1) < EPS) {
                        // Проверим, что для всех a выполняется условие
                        bool ok = true;
                        for (int a = 0; a < N; a++) {
                            double val = q0*M[0][a] + q1*M[1][a] + q2*M[2][a];
                            if (val + EPS < t) {
                                ok = false;
                                break;
                            }
                        }
                        if (ok) {
                            ans = max(ans, t);
                        }
                    }
                }
            }
        }

        results.push_back(ans);
    }

    for (double res : results) {
        cout << res << "\n";
    }

    return 0;
}