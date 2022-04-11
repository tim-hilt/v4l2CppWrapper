#include "v4l2_capture.hpp"

#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstring>
#include <iomanip>
#include <iostream>

#include "utils.hpp"

#define CLEAR(x) memset(&(x), 0, sizeof(x))

v4l2Capture::V4L2Capturer::V4L2Capturer() = default;

v4l2Capture::V4L2Capturer::V4L2Capturer(std::string devName)
    : devName(std::move(devName)) {}

auto v4l2Capture::V4L2Capturer::init() -> int {
  fd = open(devName.c_str(), O_RDWR);

  if (fd == -1) {
    std::cerr << "Failed to open capture device " << devName << "\n";
    return -1;
  }

  std::cout << "File handle to capture device: " << fd << "\n";
  return 0;
}

auto v4l2Capture::V4L2Capturer::queryCapabilities() const -> int {
  struct v4l2_capability cap {};
  CLEAR(cap);

  if (-1 == xioctl(VIDIOC_QUERYCAP, &cap)) {
    if (EINVAL == errno) {
      std::cerr << devName << " is no V4L2 device\n";
      return -1;
    }
    std::cerr << "VIDIOC_QUERYCAP\n";
    return -2;
  }

  printCapabilities(cap);
  return 0;
}

void v4l2Capture::V4L2Capturer::printCapabilities(
    struct v4l2_capability cap) const {
  std::cout << "\nDriver capabilities:\n";
  std::cout << "Driver: " << cap.driver << "\n";
  std::cout << "Card: " << cap.card << "\n";
  std::cout << "Version: " << cap.version << "\n";
  std::cout << "Capabilities:\n";

  for (auto capability :
       {V4L2_CAP_VIDEO_CAPTURE, V4L2_CAP_READWRITE, V4L2_CAP_STREAMING}) {
    if (!(cap.capabilities & capability)) {
      std::cerr << "Driver does not support " << utils::printHex(capability)
                << "\n";
    }
  }
}

void v4l2Capture::V4L2Capturer::closeVideoDevice() {
  std::cout << "Close video-device\n";
}

auto v4l2Capture::V4L2Capturer::xioctl(int request, void *arg) const -> int {
  int r = 0;
  do {
    r = ioctl(fd, request, arg);
  } while (-1 == r && EINTR == errno);
  return r;
}

void v4l2Capture::V4L2Capturer::readFrame() { std::cout << "read frame\n"; }

v4l2Capture::V4L2Capturer::~V4L2Capturer() { close(fd); }