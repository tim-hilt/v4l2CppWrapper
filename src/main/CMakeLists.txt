add_executable(v4l2-capture main.cpp)

target_link_libraries(v4l2-capture PRIVATE v4l2-capture-lib)
