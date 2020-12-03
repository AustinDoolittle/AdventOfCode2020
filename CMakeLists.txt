cmake_minimum_required(VERSION 3.17)
project(AdventOfCode2020)

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# day 1
add_executable(day1_1 day1/day1_1.cpp)
add_executable(day1_2 day1/day1_2.cpp)

# day 2
add_executable(day2_1 day2/day2_1.cpp)
add_executable(day2_2 day2/day2_2.cpp)
