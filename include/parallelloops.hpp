#ifndef PARALLELLOOPS_HPP
#define PARALLELLOOPS_HPP

#include <algorithm>  
#include <array>
#include <cassert>
#include <deque>
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

        auto threadPool =  std::vector<std::thread>();

        for (auto it = begin; it != end; it++) {
            threadPool.push_back(std::thread(function, std::ref(*it)));
        }

        std::for_each(threadPool.begin(), threadPool.end(), [](std::thread & thread) { if (thread.joinable()) thread.join(); });
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
        
        auto threadPool =  std::deque<std::thread>();
        auto iteratorBound = size / threadPoolSize;
        for(int i = 0; i < threadPoolSize; i++)
        {
            if(i == threadPoolSize - 1) // last element
            {   
                const auto bound = iteratorBound;
                iteratorBound = (size / threadPoolSize) + size % threadPoolSize;
                threadPool.push_back(std::thread(threadFunction, begin + (bound * i), iteratorBound));
                break;
            }
            
            threadPool.push_back(std::thread(threadFunction, begin + (iteratorBound * i), iteratorBound));
        }

        std::for_each(threadPool.begin(), threadPool.end(), [](std::thread & thread) { if (thread.joinable()) thread.join(); });
    };
}

#endif