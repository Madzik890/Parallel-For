#ifndef PARALLELLOOPS_HPP
#define PARALLELLOOPS_HPP

#include <array>
#include <cassert>
#include <functional>
#include <future>
#include <vector>
#include <iostream>

namespace Parallel
{
    template<typename Iterator, typename Function>
    static void Foreach(Iterator begin, Iterator end, Function function) noexcept
    {
        const auto size = end - begin;
        assert(size > 0);

        auto threadPool =  std::vector<std::thread>(size);

        for (auto it = begin; it != end; it++) {
            threadPool[it - begin] = std::thread(function, std::ref(*it));
        }

        std::for_each(threadPool.begin(), threadPool.end(), [](std::thread & thread) { if (thread.joinable()) thread.join(); });
    };

    template<typename Iterator, typename Function>
    static void ForeachRestricted(const int maxThreads, Iterator begin, Iterator end, Function function) noexcept
    {
        auto threadPoolSize = 0;
        {
            const auto size = end - begin;        
            threadPoolSize = std::min(size, maxThreads);            
        }

        assert(threadPoolSize > 0);
        
        auto threadPool =  std::vector<std::thread>(threadPoolSize);

        for (auto it = begin; it != end; it++) {
            threadPool[it - begin] = std::thread(function, std::ref(*it));
        }

        std::for_each(threadPool.begin(), threadPool.end(), [](std::thread & thread) { if (thread.joinable()) thread.join(); });
    };
}

#endif