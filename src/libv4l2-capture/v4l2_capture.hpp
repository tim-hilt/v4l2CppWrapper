#ifndef V4L2_CAPTURE_INCLUDED
#define V4L2_CAPTURE_INCLUDED

#include <linux/videodev2.h>
#include <sys/types.h>

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

struct buffer_addr {
  void *start;
  size_t length;
} __attribute__((aligned(16)));

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
  int32_t fd{-1};

  /**
   * @brief Width of capture
   *
   */
  uint32_t width{DEFAULT_WIDTH};

  /**
   * @brief Heigth of capture
   *
   */
  uint32_t height{DEFAULT_HEIGHT};

  /**
   * @brief File-format of capture
   *
   */
  static const unsigned int PIXFMT = V4L2_PIX_FMT_YUYV;

  static const unsigned int BUFCOUNT = 4;

  static const unsigned int BUFCOUNT_MIN = 3;

  std::vector<buffer_addr> buf_addr{BUFCOUNT};

  /**
   * @brief Set capture format
   *
   * @return int 0 if no error occured
   */
  [[nodiscard("Error value must be obtained")]] auto setFormat() const -> int;

  /**
   * @brief Request buffers to enqueue
   *
   * @return int 0 if no errors occured
   */
  [[nodiscard("Error value must be obtained")]] auto requestBuffers() -> int;

  /**
   * @brief Meta ioctl-wrapper, that retries the operation, if the system call
   *        was interrupted
   *
   * @param request ioctl command to execute
   * @param arg data-structure to read/write on
   * @return int whether or not execution was successful
   */
  [[nodiscard("Error value must be obtained")]] auto xioctl(uint32_t request,
                                                            void *arg) const
      -> int;

 public:
  /**
   * @brief Construct a new V4L2Capturer object
   *
   */
  V4L2Capturer();

  /**
   * @brief Construct a new V4L2Capturer object
   *
   * @param devName Name of the device used for capturing
   */
  explicit V4L2Capturer(std::string devName);

  /**
   * @brief Construct a new V4L2Capturer object
   *
   * @param devName Name of the device used for capturing
   * @param width Width of the capture
   * @param height Height of the capture
   */
  explicit V4L2Capturer(std::string devName, unsigned int width,
                        unsigned int height);

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
  [[nodiscard("Error value must be obtained")]] auto init() -> int;

  /**
   * @brief Read frame from video device
   *
   */
  [[noreturn]] void readFrame();
};

}  // namespace v4l2Capture

#endif  // V4L2_CAPTURE_INCLUDED