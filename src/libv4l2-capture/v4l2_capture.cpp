#include "v4l2_capture.hpp"

#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cerrno>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <utility>

/*
 * IDEAS ON HOW TO IMPROVE
 * - Add cli-interface
 * - Let user select options interactively by querying possible parameters
 * - Add map [int8_t errorCode]std::string errorMsg
 */

auto v4l2Capture::V4L2Capturer::setFormat(uint16_t width, uint16_t height,
                                          uint32_t pixformat) const -> int8_t {
  v4l2_format fmt{};
  util::clear(fmt);

  fmt.fmt.pix.width = width;
  fmt.fmt.pix.height = height;
  fmt.fmt.pix.bytesperline = fmt.fmt.pix.width * 2U;
  fmt.fmt.pix.sizeimage = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
  fmt.fmt.pix.colorspace = V4L2_COLORSPACE_DEFAULT;
  fmt.fmt.pix.field = V4L2_FIELD_ANY;
  fmt.fmt.pix.pixelformat = pixformat;
  fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if (-1 == xioctl(VIDIOC_S_FMT, &fmt)) {
    std::cerr << "Setting format failed\n";
    return -1;
  }

  return 0;
}

auto v4l2Capture::V4L2Capturer::requestBuffers() -> int8_t {
  v4l2_requestbuffers req{};
  util::clear(req);

  req.count = BUFCOUNT;
  req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  req.memory = V4L2_MEMORY_MMAP;

  if (-1 == xioctl(VIDIOC_REQBUFS, &req)) {
    if (EINVAL == errno) {
      std::cerr << devName << " does not support memory mapping\n";
      return -1;
    }
    std::cerr << "VIDIOC_REQBUFS failed\n";
    return -1;
  }

  if (req.count < BUFCOUNT_MIN) {
    std::cerr << "Insufficient buffer memory on " << devName << "\n";
    return -1;
  }

  if (req.count != buf_addr.size()) {
    buf_addr.resize(req.count);
  }

  for (size_t i = 0; i < req.count; ++i) {
    v4l2_buffer buf{};
    util::clear(buf);

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = i;

    if (-1 == xioctl(VIDIOC_QUERYBUF, &buf)) {
      std::cerr << "VIDIOC_QUERYBUF\n";
      return -1;
    }

    buf_addr.at(i).length = buf.length;
    // TODO: Does this produce a memory leak? I don't unmap anything -> yes!
    buf_addr.at(i).start =
        static_cast<char *>(mmap(nullptr, buf.length, PROT_READ | PROT_WRITE,
                                 MAP_SHARED, fd, buf.m.offset));

    if (MAP_FAILED == buf_addr.at(i).start) {
      std::cerr << "mmap\n";
      return -1;
    }
  }
  return 0;
}

auto v4l2Capture::V4L2Capturer::enqueuePrimeBuffers() const -> int8_t {
  for (size_t i = 0; i < BUFCOUNT; ++i) {
    v4l2_buffer buf{};
    util::clear(buf);

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = i;

    if (-1 == xioctl(VIDIOC_QBUF, &buf)) {
      std::cerr << "VIDIOC_QBUF\n";
      return -1;
    }
  }
  return 0;
}

auto v4l2Capture::V4L2Capturer::enableStreaming() const -> int8_t {
  int a = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if (-1 == xioctl(VIDIOC_STREAMON, &a)) {
    std::cerr << "VIDIOC_STREAMON\n";
    return -1;
  }
  return 0;
}

auto v4l2Capture::V4L2Capturer::xioctl(uint32_t request, void *arg) const
    -> int8_t {
  int8_t r = 0;
  do {
    r = ioctl(fd, request, arg);
  } while (-1 == r && EINTR == errno);
  return r;
}

v4l2Capture::V4L2Capturer::V4L2Capturer() = default;

v4l2Capture::V4L2Capturer::V4L2Capturer(std::string devName)
    : devName(std::move(devName)) {}

v4l2Capture::V4L2Capturer::~V4L2Capturer() { close(fd); }

auto v4l2Capture::V4L2Capturer::init(uint16_t width, uint16_t height,
                                     uint32_t pixformat) -> int8_t {
  fd = open(devName.c_str(), O_RDWR);

  if (fd == -1) {
    std::cerr << "Failed to open capture device " << devName << "\n";
    return -1;
  }

  int8_t err = setFormat(width, height, pixformat);

  if (err != 0) {
    return err;
  }

  err = requestBuffers();

  if (err != 0) {
    return err;
  }

  err = enqueuePrimeBuffers();

  if (err != 0) {
    return err;
  }

  err = enableStreaming();

  if (err != 0) {
    return err;
  }

  return 0;
}
