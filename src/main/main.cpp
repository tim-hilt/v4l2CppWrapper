#include <cstdlib>
#include <v4l2_capture.hpp>

#define DEV_NAME "/dev/video4"
#define WIDTH 1920
#define HEIGHT 1080

auto main() -> int {
  // auto capturer = v4l2Capture::V4L2Capturer(DEV_NAME, WIDTH, HEIGHT);
  v4l2Capture::V4L2Capturer capturer;
  int err = capturer.init();

  if (err != 0) {
    return EXIT_FAILURE;
  }

  // while (true) {
  //   // stream video
  // }

  return EXIT_SUCCESS;
}