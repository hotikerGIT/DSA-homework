#include <iostream>

bool check_win(const char board[][3], char who) {
    for (int i = 0; i < 3; ++i) {
        bool win = true;
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != who) win = false;
        }

        if (win) return win;
    }

    for (int i = 0; i < 3; ++i) {
        bool win = true;
        for (int j = 0; j < 3; ++j) {
            if (board[j][i] != who) win = false;
        }

        if (win) return win;
    }

    bool win = true;
    for (int i = 0; i < 3; ++i) {
        if (board[i][i] != who) win = false;
    }

    if (win) return win;

    win = true;
    for (int i = 0; i < 3; ++i) {
        if (board[2 - i][i] != who) win = false;
    }

    if (win) return win;

    return false;
}

int main() {
    char board[3][3];
    int x_cnt = 0;
    int o_cnt = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cin >> board[i][j];

            x_cnt += board[i][j] == 'X';
            o_cnt += board[i][j] == '0';
        }
    }

    if (x_cnt > o_cnt + 1 || o_cnt > x_cnt) {
        std::cout << "illegal";
        return 0;
    }

    bool first_win = check_win(board, 'X');
    bool second_win = check_win(board, '0');

    if (first_win && second_win || first_win && x_cnt != o_cnt + 1 || second_win && o_cnt != x_cnt) {
        std::cout << "illegal";
        return 0;
    }

    if (first_win) {
        std::cout << "the first player won";
        return 0;
    }

    if (second_win) {
        std::cout << "the second player won";
        return 0;
    }

    if (x_cnt + o_cnt == 9) {
        std::cout << "draw";
        return 0;
    }

    if (x_cnt == o_cnt) {
        std::cout << "first";
        return 0;
    }

    std::cout << "second";
}