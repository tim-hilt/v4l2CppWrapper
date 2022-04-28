#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <ratio>
#include <string>
#include <string_view>
#include <v4l2_capture.hpp>

#include "spdlog/spdlog.h"

constexpr std::string_view DEVNAME_EXTERNAL{"/dev/video4"};
constexpr uint16_t WIDTH_EXTERNAL{1920};
constexpr uint16_t HEIGHT_EXTERNAL{1080};

constexpr uint16_t MILLIS_IN_SECOND{1000};

void imageToFile(const buffer_addr &buf_addr) {
  auto file = std::fstream("test.yuy", std::ios::out | std::ios::binary);
  file.write(buf_addr.start, buf_addr.length);
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
    spdlog::info("Current fps: {}", i);
    i = 0;
    t_start = std::chrono::high_resolution_clock::now();
  }
}

void nop([[maybe_unused]] const buffer_addr &buf_addr) {}

auto main() -> int {
  // v4l2Capture::V4L2Capturer capturer{DEVNAME_EXTERNAL.data()};
  v4l2Capture::V4L2Capturer capturer{};

  if (capturer.init(640, 480) != 0) {
    return EXIT_FAILURE;
  }

  while (true) {
    if (capturer.handleCapture(nop) != 0) {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
