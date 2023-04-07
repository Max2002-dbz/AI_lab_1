#pragma once

#include <vector>

class Vidpal
{
public:
    Vidpal();
    ~Vidpal();

    std::vector<int> get_vidpal(std::size_t n);

private:
    void vidpal(std::size_t n);
    int conflicts();

    double temp = 100;
    double cooling_rate = 0.99;
    std::vector<int> board;
};
