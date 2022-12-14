#include <iostream>
#include <chrono>
#include <random>
#include <vector>

#include "../include/parallelloops.hpp"

constexpr const auto VECTOR_SIZE = 90000000;
static std::vector<int> vector(VECTOR_SIZE);

auto GenerateFunction = [](int value) {
    static thread_local std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(-10000000,10000000);
    value = distribution(generator);
};

inline void generate() noexcept
{     
    std::for_each(vector.begin(), vector.end(), GenerateFunction);    
}

inline void parallelGenerate() noexcept
{ 
    Parallel::ForeachRestricted(vector.begin(), vector.end(), GenerateFunction);
}

inline void sort() noexcept
{
    std::sort(vector.begin(), vector.end(), [](int a, int b) {
        return a > b;
    });
}

inline void parallelSort() noexcept
{
    Parallel::SortRestricted(vector.begin(), vector.end());
}

int main()
{
    /*{
        const auto begin = std::chrono::steady_clock::now();
        generate();
        const auto end = std::chrono::steady_clock::now();
        std::cout << "Single thread generate  : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    }

    {
        const auto begin = std::chrono::steady_clock::now();
        parallelGenerate();
        const auto end = std::chrono::steady_clock::now();
        std::cout << "Parallel thread generate: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    }*/

    std::vector<int> xd = {1, 3, 2, 5, 4, 7, 63, 11, 32, 523, 12, 55, 5, 4, 7, 63, 11, 32, 523, 12, 55, 5, 4, 7, 63, 11, 32, 523, 12, 55, 5, 4, 7, 63, 11, 32, 523, 12, 55};
    Parallel::SortRestricted(xd.begin(), xd.end());

    for(const auto &el : xd)
    {
        std::cout << el << " ";
    }

    std::cout<< std::endl;

    /*{
        const auto begin = std::chrono::steady_clock::now();
        generate();
        const auto end = std::chrono::steady_clock::now();
        std::cout << "Single thread generate  : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    }

    {
        const auto begin = std::chrono::steady_clock::now();
        parallelGenerate();
        const auto end = std::chrono::steady_clock::now();
        std::cout << "Parallel thread generate: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;
    }*/

    return 0;
}