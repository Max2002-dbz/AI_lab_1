#include "vidpal.h"
#include <random>

Vidpal::Vidpal()
{

}

Vidpal::~Vidpal()
{

}

void Vidpal::vidpal(std::size_t n)
{
    int current_conflicts = conflicts();
    while (current_conflicts > 0 && temp > 1e-6) {
        int i = rand() % n;
        int j = rand() % n;
        int tmp = board[i];
        board[i] = j;
        int new_conflicts = conflicts();
        int delta = new_conflicts - current_conflicts;
        if (delta < 0 || exp(-delta / temp) > (double)rand() / RAND_MAX) {
            current_conflicts = new_conflicts;
        }
        else {
            board[i] = tmp;
        }
        temp *= cooling_rate;
    }
    temp = 100;
}

int Vidpal::conflicts()
{
    int n = board.size();
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (board[i] == board[j] || abs(i - j) == abs(board[i] - board[j])) {
                count++;
            }
        }
    }
    return count;
}

std::vector<int> Vidpal::get_vidpal(std::size_t n)
{
    srand(time(0));
    board.clear();
    board.resize(n);

    for (int i = 0; i < n; i++) {
        board[i] = rand() % n;
    }

    vidpal(n);

    if (conflicts() == 0) {
        return board;
    }

    return std::vector<int>();
}