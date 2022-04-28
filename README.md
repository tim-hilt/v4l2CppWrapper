# V4L2 C++ Wrapper

A tiny wrapper around the V4L2-Kernel-API to capture and act upon images.

---

## Dependencies

### Required

To run the project, the following dependencies have to be installed:

- Clang
- CMake
- Ninja

### Optionally

- Include What You Use
- Cppcheck
- Cpplint

If you don't want to enable the checkers, just comment them out in the root `CMakeLists.txt`.

### Library dependencies

- Spdlog
- Catch2

## Running the project

``` bash
cmake -B build
cmake --build build
```

If you have `vcpkg` installed, you can install the dependencies by passing `-DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake` during cmake configuration.

