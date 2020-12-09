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

# day 5
add_executable(day5_1 src/day5/day5_1.cpp)
add_executable(day5_2 src/day5/day5_2.cpp)

# day 6
add_executable(day6_1 src/day6/day6_1.cpp)
add_executable(day6_2 src/day6/day6_2.cpp)

# day 7
add_executable(day7_1 src/day7/day7_1.cpp)
add_executable(day7_2 src/day7/day7_2.cpp)

# day 8
add_executable(day8_1 src/day8/day8_1.cpp)
add_executable(day8_2 src/day8/day8_2.cpp)
