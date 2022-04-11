#include "v4l2_capture.hpp"

#include <iostream>
#include <sys/ioctl.h>

void v4l2Capture::openVideoDevice() { std::cout << "Open video-device\n"; }

void v4l2Capture::closeVideoDevice() { std::cout << "Close video-device\n"; }

int v4l2Capture::xioctl(int fh, int request, void *arg) {
  int r = 0;
  do {
    r = ioctl(fh, request, arg);
  } while (-1 == r && EINTR == errno);
  return r;
}

void v4l2Capture::mmap() { std::cout << "mmap\n"; }

void v4l2Capture::readFrame() { std::cout << "read frame\n"; }