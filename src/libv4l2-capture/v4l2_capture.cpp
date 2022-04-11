#include "v4l2_capture.hpp"

#include <iostream>

void v4l2Capture::openVideoDevice() { std::cout << "Open video-device\n"; }

void v4l2Capture::closeVideoDevice() { std::cout << "Close video-device\n"; }

void v4l2Capture::ioctl() { std::cout << "ioctl\n"; }

void v4l2Capture::mmap() { std::cout << "mmap\n"; }

void v4l2Capture::readFrame() { std::cout << "read frame\n"; }