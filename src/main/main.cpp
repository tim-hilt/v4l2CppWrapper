#include <cstdlib>
#include <iostream>
#include <string>
#include <v4l2_capture.hpp>

#define DEV_NAME "/dev/video4"
#define WIDTH 1920
#define HEIGHT 1080

void imageToFile(buffer_addr buf_addr) {
  auto file = std::fstream("test.yuy", std::ios::out | std::ios::binary);
  file.write(static_cast<char *>(buf_addr.start), buf_addr.length);
  file.close();
}

auto main() -> int {
  // auto capturer = v4l2Capture::V4L2Capturer(DEV_NAME, WIDTH, HEIGHT);
  v4l2Capture::V4L2Capturer capturer;

  if (capturer.init() != 0) {
    return EXIT_FAILURE;
  }

  while (true) {
    if (capturer.handleCapture([](buffer_addr base) {}) != 0) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}