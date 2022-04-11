#include <cstdlib>
#include <v4l2_capture.hpp>

#define DEV_NAME "/dev/video4"

auto main() -> int {
  v4l2Capture::V4L2Capturer capturer = v4l2Capture::V4L2Capturer(DEV_NAME);
  int err = capturer.init();

  if (err != 0) {
    return EXIT_FAILURE;
  }

  capturer.queryCapabilities();

  // while (true) {
  //   // stream video
  // }
}