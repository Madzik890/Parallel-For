cmake_minimum_required(VERSION 3.8)

project(ParallelBenchmark)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -latomic")
find_package(Threads REQUIRED)

file(GLOB ParallelBenchmark_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")

include_directories(${PROJECT_SOURCE_DIR}../include)

add_executable(ParallelBenchmark ${ParallelBenchmark_src})
target_link_libraries(ParallelBenchmark Threads::Threads -ltbb)

