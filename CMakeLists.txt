# Currently installed version
cmake_minimum_required(VERSION 3.23)
project(v4l2-capture VERSION 0.1.0)

# Exports compile_commands.json to help clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include what you use optimizes includes
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)

add_subdirectory(src)
