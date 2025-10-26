cmake_minimum_required(VERSION 3.15)
project(calculator_gmock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
include(CTest)

add_subdirectory(src)
add_subdirectory(test)
