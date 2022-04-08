# Currently installed version
cmake_minimum_required(VERSION 3.23)
project(v4l2-capture VERSION 0.1.0)

# Exports compile_commands.json to help clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(v4l2-capture-lib v4l2_capture.hpp v4l2_capture.cpp)

add_executable(v4l2-capture main.cpp)

target_link_libraries(v4l2-capture PRIVATE v4l2-capture-lib)
