add_library(v4l2-capture-lib v4l2_capture.hpp v4l2_capture.cpp)

target_include_directories(v4l2-capture-lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")