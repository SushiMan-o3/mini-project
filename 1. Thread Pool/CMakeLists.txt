cmake_minimum_required(VERSION 3.15)
project(ThreadPool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_library(ThreadPool src/ThreadPool.cpp)
target_include_directories(ThreadPool PUBLIC include)
target_link_libraries(ThreadPool PUBLIC Threads::Threads)

enable_testing()
add_executable(thread_pool_tests tests/test_threadpool.cpp)
target_link_libraries(thread_pool_tests PRIVATE ThreadPool)
add_test(NAME ThreadPoolTests COMMAND thread_pool_tests)
