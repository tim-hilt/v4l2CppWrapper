cmake_minimum_required(VERSION 3.23)
project(v4l2-capture LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_GENERATOR "Ninja Multi-Config")

set(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)

# set(CMAKE_CXX_CLANG_TIDY clang-tidy)

# set(CMAKE_CXX_CPPCHECK cppcheck --std=c++20)

# set(CMAKE_CXX_CPPLINT cpplint)

# set(CMAKE_LINK_WHAT_YOU_USE ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

include(CTest)

add_subdirectory(src)
add_subdirectory(test)
