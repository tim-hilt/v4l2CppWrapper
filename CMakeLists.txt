# Currently installed version
cmake_minimum_required(VERSION 3.23)
project(v4l2-capture VERSION 0.1.0)

set(CMAKE_GENERATOR "Ninja Multi-Config")

set(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)

set(CMAKE_CXX_CPPCHECK cppcheck --std=c++17)

set(CMAKE_CXX_CPPLINT cpplint)

set(CMAKE_LINK_WHAT_YOU_USE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
