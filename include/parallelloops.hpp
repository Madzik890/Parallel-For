#ifndef PARALLELLOOPS_HPP
#define PARALLELLOOPS_HPP

#include <algorithm>  
#include <array>
#include <cassert>
#include <vector>
#include <functional>
#include <future>

namespace Parallel
{    
    static const auto DEFAULT_MAX_THREADS = std::thread::hardware_concurrency();

    template<typename Iterator, typename Function>
    static void Foreach(Iterator &&begin, Iterator &&end, Function &&function) noexcept
    {
        const auto size = end - begin;
        assert(size > 0);

        auto threadPool =  std::vector<std::future<void>>(size);
        for (auto it = begin; it != end; it++) {
            threadPool.push_back(std::async(function, std::ref(*it)));
        }                
    };

    template<typename Iterator, typename Function>
    static void ForeachRestricted(Iterator &&begin, Iterator &&end, Function &&function, const long int maxThreads = DEFAULT_MAX_THREADS) noexcept
    {
        const auto size = end - begin;                
        const auto threadPoolSize = std::min(size, maxThreads);            
    
        assert(threadPoolSize > 0);    

        auto threadFunction = [function](Iterator it, const int to) {
            for(int i = 0; i < to; i++)
            {
                auto iterator = (it + i);
                auto itRef = std::ref(*iterator);      
                function(itRef);          
            }
        };   
        
        auto threadPool =  std::vector<std::future<void>>(threadPoolSize);
        auto iteratorBound = size / threadPoolSize;
        for(int i = 0; i < threadPoolSize; i++)
        {
            if(i == threadPoolSize - 1) // last element
            {   
                const auto bound = iteratorBound;
                iteratorBound = (size / threadPoolSize) + size % threadPoolSize;
                threadPool[i] = std::async(threadFunction, begin + (bound * i), iteratorBound);
                break;
            }
                        
            threadPool[i] = std::async(threadFunction, begin + (iteratorBound * i), iteratorBound);
        }      
    };
}

#endif