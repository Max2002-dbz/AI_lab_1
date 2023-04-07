#pragma once

#include <vector>

class MyAlgorithm
{
public:
    MyAlgorithm(){};
    ~MyAlgorithm(){};

    bool isSafe(int row, int col);
    bool solveNQueens(int col);
    std::vector<int>get_result(int n);

private:
    int N;
    int **board = nullptr;
    std::vector<int> result;
};
