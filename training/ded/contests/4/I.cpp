#include <iostream>
#include <vector>

int main() {
    freopen("tic-tac-toe.in", "r", stdin);
    freopen("tic-tac-toe.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<char>> board(n, std::vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> board[i][j];
        }
    }

    bool flag = false;
    for (int i = 0; i < n - 4; ++i) {
        for (int j = 0; j < m; ++j) {
            bool ver_o = true;
            bool ver_x = true;

            for (int add = 0; add < 5; ++add) {
                if (board[i + add][j] != 'X') ver_x = false;
                if (board[i + add][j] != 'O') ver_o = false;
            }

            if (ver_o || ver_x) {
                flag = true;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 4; ++j) {
            bool hor_o = true;
            bool hor_x = true;

            for (int add = 0; add < 5; ++add) {
                if (board[i][j + add] != 'X') hor_x = false;
                if (board[i][j + add] != 'O') hor_o = false;
            }

            if (hor_o || hor_x) {
                flag = true;
                break;
            }
        }
    }

    for (int i = 0; i < n - 4; ++i) {
        for (int j = 0; j < m - 4; ++j) {
            bool diag_o = true;
            bool diag_x = true;

            for (int add = 0; add < 5; ++add) {
                if (board[i + add][j + add] != 'X') diag_x = false;
                if (board[i + add][j + add] != 'O') diag_o = false;
            }

            if (diag_o || diag_x) {
                flag = true;
                break;
            }
        }
    }

    for (int i = 0; i < n - 4; ++i) {
        for (int j = 4; j < m; ++j) {
            bool diag_o = true;
            bool diag_x = true;

            for (int add = 0; add < 5; ++add) {
                if (board[i + add][j - add] != 'X') diag_x = false;
                if (board[i + add][j - add] != 'O') diag_o = false;
            }

            if (diag_o || diag_x) {
                flag = true;
                break;
            }
        }
    }

    if (flag) std::cout << "Yes";
    else std::cout << "No";
}