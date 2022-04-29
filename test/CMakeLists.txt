find_package(Catch2 CONFIG REQUIRED)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE v4l2-capture-lib Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)
