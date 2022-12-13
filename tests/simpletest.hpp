#ifndef SIMPLETEST_HPP
#define SIMPLETEST_HPP

#include <boost/test/included/unit_test.hpp>
#include <vector>

#include "../include/parallelloops.hpp"

BOOST_AUTO_TEST_CASE(SimpleTest)
{
    std::vector<int> vector(5);    
    Parallel::Foreach(vector.begin(), vector.end(), [](int &value) {        
        value = 123;
    });
    
    Parallel::Foreach(vector.begin(), vector.end(), [](const int& value) {
        std::cerr << value << std::endl;    
    });

    BOOST_ASSERT(true == true);
}

#endif