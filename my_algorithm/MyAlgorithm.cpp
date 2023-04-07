#include "MyAlgorithm.h"


bool MyAlgorithm::solveNQueens(int col)
{
// Якщо всі ферзі розміщено, повернути true
    if (col >= N) {
        return true;
    }
    // Перебрати рядки і спробувати розмістити ферзя у кожному з них
    for (int i = 0; i < N; i++) {
        // Перевірити, чи можна розмістити ферзя у даній позиції
        if (isSafe(i, col)) {
            // Розмістити ферзя на дошці
            result[i] = col;
            board[i][col] = 1;
            // Рекурсивно викликати функцію для розміщення наступного ферзя
            if (solveNQueens(col + 1)) {
                return true;
            }
            // Якщо розміщення не було успішним, відмінити дію
            board[i][col] = 0;
        }
    }
    // Якщо не вдалося розмістити ферзя, повернути false
    return false;
}

bool MyAlgorithm::isSafe(int row, int col)
{
    // Перевірка стовпця
    for (int i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
    }
    // Перевірка діагоналі зліва вгору
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }
    // Перевірка діагоналі зліва вниз
    for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }
    return true;
}

std::vector<int> MyAlgorithm::get_result(int n)
{
    N = n;

    board = new int*[N];
    for (int i = 0; i < N; ++i) {
        board[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            board[i][j] = 0;
        }
    }
    result.resize(N);

    bool r = solveNQueens(0);

    for (int i = 0; i < N; ++i) {
        delete[] board[i];
    }
    delete[] board;

    if (r) {
        return result;
    }

    return std::vector<int>();
}
