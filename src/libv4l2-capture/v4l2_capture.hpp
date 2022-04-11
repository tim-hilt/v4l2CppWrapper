#ifndef V4L2_CAPTURE_INCLUDED
#define V4L2_CAPTURE_INCLUDED

#include <linux/videodev2.h>

#include <cstdint>
#include <fstream>
#include <string>

namespace v4l2Capture {

class V4L2Capturer {
  /**
   * @brief name of device on which to capture
   *
   */
  std::string devName{"/dev/video0"};

  /**
   * @brief File descriptor of video-device. I have to
   *
   */
  int fd{-1};

  /**
   * @brief Print v4l2 capabilities
   *
   * @param cap v4l2 capabilities
   */
  void printCapabilities(struct v4l2_capability cap) const;

  /**
   * @brief Use this function before giving parameters to V4L2-API
   *
   * @param param the parameter to clear
   */
  static void clearV4L2Parameter(void *param);

 public:
  /**
   * @brief Construct a new V4L2Capturer object
   *
   */
  V4L2Capturer();

  /**
   * @brief Construct a new V4L2Capturer object and initialize device to devName
   *
   * @param devName
   */
  explicit V4L2Capturer(std::string devName);

  /**
   * @brief Destroy the V4L2Capturer object
   *
   */
  ~V4L2Capturer();

  /**
   * @brief Opens a video device
   *
   * @return int 0 if no error
   */
  auto init() -> int;

  /**
   * @brief Prints out the capabilities of the video device
   *
   * @return int 0 if no error
   */
  auto queryCapabilities() const -> int;

  /**
   * @brief Closes a video device
   *
   */
  void closeVideoDevice();

  /**
   * @brief Meta ioctl-wrapper, that retries the operation, if the system call
   *        was interrupted
   *
   * @param request ioctl command to execute
   * @param arg data-structure to read/write on
   * @return int whether or not execution was successful
   */
  auto xioctl(int request, void *arg) const -> int;

  /**
   * @brief Read frame from video device
   *
   */
  void readFrame();
};

}  // namespace v4l2Capture

#endif  // V4L2_CAPTURE_INCLUDED