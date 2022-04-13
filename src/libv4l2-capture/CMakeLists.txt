add_library(v4l2-capture-lib v4l2_capture.hpp v4l2_capture.cpp utils.hpp utils.cpp)

target_compile_options(v4l2-capture-lib PRIVATE -Wall -Wextra)
target_include_directories(v4l2-capture-lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
