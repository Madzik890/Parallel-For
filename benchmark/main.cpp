#include <iostream>
#include <chrono>
#include <vector>

#include "../include/parallelloops.hpp"

constexpr const auto VECTOR_SIZE = 100000000;

auto GenerateFunction = [](int &value) {
    do
    {
        value = rand() + 1;        
    }
    while(value == 0); 
};

void generate() noexcept
{
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> vector(VECTOR_SIZE);
    for(auto &it : vector)
    {
        GenerateFunction(it);
    }
}

void parallelGenerate() noexcept
{
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> vector(VECTOR_SIZE);

    Parallel::ForeachRestricted(vector.begin(), vector.end(), GenerateFunction, 2);
}

int main()
{
    {
        const auto begin = std::chrono::steady_clock::now();
        generate();
        const auto end = std::chrono::steady_clock::now();
        std::cout << "Single thread generate  : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    }

    {
        const auto begin = std::chrono::steady_clock::now();
        parallelGenerate();
        const auto end = std::chrono::steady_clock::now();
        std::cout << "Parallel thread generate: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " ms" << std::endl;
    }

    return 0;
}