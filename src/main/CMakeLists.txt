add_executable(v4l2-capture main.cpp)

target_compile_options(v4l2-capture PRIVATE -Wall -Wextra)
target_link_libraries(v4l2-capture PRIVATE spdlog::spdlog v4l2-capture-lib)
