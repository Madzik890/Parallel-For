#ifndef SIMPLETEST_HPP
#define SIMPLETEST_HPP

#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <ctime>

#include "../include/parallelloops.hpp"

BOOST_AUTO_TEST_CASE(SimpleTest)
{
    std::vector<int> vector = {1, 2, 3, 4, 5};
    Parallel::Foreach(vector.begin(), vector.end(), [](int &value)
                      { value *= value; });

    const auto vectorSize = vector.size();
    for (int i = 0; i < vectorSize; i++)
    {
        const auto exceptedValue = i + 1;
        const auto value = vector[i] / exceptedValue;
        BOOST_ASSERT(exceptedValue == value);
    }
}

BOOST_AUTO_TEST_CASE(ForeachRestricted)
{
    std::vector<int> vector = {1, 2, 3, 4, 5};
    Parallel::ForeachRestricted( vector.begin(), vector.end(), [](int &value)
    { 
        value *= value; 
    }, 2);

    const auto vectorSize = vector.size();
    for (int i = 0; i < vectorSize; i++)
    {
        const auto exceptedValue = i + 1;
        const auto value = vector[i] / exceptedValue;
        BOOST_ASSERT(exceptedValue == value);
    }
}

BOOST_AUTO_TEST_CASE(ForeachRestricted1024)
{
    constexpr const auto VECTOR_SIZE = 1024;

    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> vector(VECTOR_SIZE);
    std::generate(vector.begin(), vector.end(), std::rand);
    const auto copyVector = vector;

    assert(copyVector.size() == vector.size());

    Parallel::ForeachRestricted(vector.begin(), vector.end(), [](int &value)
    {
         value -= 1; 
    });

    const auto vectorSize = vector.size();
    for (int i = 0; i < vectorSize; i++)
    {
        const auto exceptedValue = copyVector[i];
        const auto value = vector[i] + 1;
        if (exceptedValue != value)
            std::cerr << exceptedValue << "!=" << value << std::endl;
        BOOST_ASSERT(exceptedValue == value);
    }
}

BOOST_AUTO_TEST_CASE(ForeachRestrictedBenchmark)
{
    constexpr const auto VECTOR_SIZE = 1234567;

    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> vector(VECTOR_SIZE);

    Parallel::ForeachRestricted(vector.begin(), vector.end(), [](int &value)
    {                        
        do
        {
            value = rand() + 1;        
        }
        while(value == 0); 
    });

    for (const auto &number : vector)
        BOOST_ASSERT(number != 0);
}

#endif