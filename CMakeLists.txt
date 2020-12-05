cmake_minimum_required(VERSION 3.17)
project(AdventOfCode2020)

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# sharing is caring
include_directories(src/shared)

# day 1
add_executable(day1_1 src/day1/day1_1.cpp)
add_executable(day1_2 src/day1/day1_2.cpp)

# day 2
add_executable(day2_1 src/day2/day2_1.cpp)
add_executable(day2_2 src/day2/day2_2.cpp)

# day 3
add_executable(day3_1 src/day3/day3_1.cpp)
add_executable(day3_2 src/day3/day3_2.cpp)

# day4
add_executable(day4_1 src/day4/day4_1.cpp)
add_executable(day4_2 src/day4/day4_2.cpp)
