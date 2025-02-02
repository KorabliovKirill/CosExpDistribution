cmake_minimum_required(VERSION 3.28)

project(CosExpDistribution)

add_executable(CosExpDistribution
    src/main.cpp
    src/distribution.cpp
    src/distribution.hpp
    src/mix_distribution.cpp
    src/mix_distribution.hpp
    src/emp_distribution.cpp
    src/emp_distribution.hpp
    tests/main_distribution_test.cpp
    tests/main_distribution_test.hpp
    tests/mix_distribution_test.cpp
    tests/mix_distribution_test.hpp
    tests/emp_distribution_test.cpp
    tests/emp_distribution_test.hpp
)