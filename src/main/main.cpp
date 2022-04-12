#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <v4l2_capture.hpp>

#define DEVNAME_EXTERNAL "/dev/video4"
#define WIDTH_EXTERNAL 1920
#define HEIGHT_EXTERNAL 1080

#define MILLIS_IN_SECOND 1000

void imageToFile(const buffer_addr &buf_addr) {
  auto file = std::fstream("test.yuy", std::ios::out | std::ios::binary);
  file.write(static_cast<char *>(buf_addr.start), buf_addr.length);
  file.close();
}

void calcFps([[maybe_unused]] const buffer_addr &buf_addr) {
  static uint32_t i{0};
  static auto t_start = std::chrono::high_resolution_clock::now();
  static auto t_end = std::chrono::high_resolution_clock::now();

  ++i;
  t_end = std::chrono::high_resolution_clock::now();
  double elapsed_time_ms =
      std::chrono::duration<double, std::milli>(t_end - t_start).count();

  if (elapsed_time_ms >= MILLIS_IN_SECOND) {
    std::cout << i << "\n";
    i = 0;
    t_start = std::chrono::high_resolution_clock::now();
  }
}

void nop([[maybe_unused]] const buffer_addr &buf_addr) {}

auto main() -> int {
  // INFO: Use this when external camera is available
  // auto capturer = v4l2Capture::V4L2Capturer(DEV_NAME);
  v4l2Capture::V4L2Capturer capturer;

  if (capturer.init() != 0) {
    return EXIT_FAILURE;
  }

  while (true) {
    if (capturer.handleCapture(calcFps) != 0) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}