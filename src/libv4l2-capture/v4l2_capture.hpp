#ifndef V4L2_CAPTURE_INCLUDED
#define V4L2_CAPTURE_INCLUDED

#include <linux/videodev2.h>
#include <sys/types.h>

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

constexpr std::string_view DEVICE{"/dev/video0"};
constexpr uint8_t BUFCOUNT{4};
constexpr uint8_t BUFCOUNT_MIN{BUFCOUNT - 1};

constexpr uint16_t DEFAULT_WIDTH{1280};
constexpr uint16_t DEFAULT_HEIGHT{720};
constexpr uint32_t DEFAULT_PIXFORMAT{V4L2_PIX_FMT_YUYV};

/**
 * @brief Embedded struct, used to save buffer-state
 *
 */
struct buffer_addr {
  void *start;
  size_t length;
};

namespace v4l2Capture {

class V4L2Capturer {
  /**
   * @brief name of device on which to capture
   *
   */
  std::string devName{DEVICE};

  /**
   * @brief File descriptor of video-device. I have to
   *
   */
  int32_t fd{-1};

  std::vector<buffer_addr> buf_addr = std::vector<buffer_addr>(BUFCOUNT);

  /**
   * @brief Set capture format
   *
   * @param width of capture
   * @param height of capture
   * @param pixformat of capture
   * @return int8_t 0 if no error occured
   */
  [[nodiscard("Error value must be obtained")]] auto setFormat(
      uint16_t width, uint16_t height, uint32_t pixformat) const -> int8_t;

  /**
   * @brief Request buffers to enqueue
   *
   * @return int 0 if no errors occured
   */
  [[nodiscard("Error value must be obtained")]] auto requestBuffers() -> int8_t;

  /**
   * @brief Enqueue buffers
   *
   * @return int8_t 0 if no errors occured
   */
  [[nodiscard("Error value must be obtained")]] auto enqueuePrimeBuffers() const
      -> int8_t;

  /**
   * @brief Enable streaming
   *
   * @return int8_t 0 if no errors occured
   */
  [[nodiscard("Error value must be obtained")]] auto enableStreaming() const
      -> int8_t;

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
      -> int8_t;

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
   * @brief Destroy the V4L2Capturer object
   *
   */
  ~V4L2Capturer();

  /**
   * @brief Opens a video device
   *
   * @return int 0 if no error
   */

  /**
   * @brief Initializes capture-device
   *
   * @param width of capture
   * @param height of capture
   * @param pixformat of capture
   * @return int8_t 0 if no error
   */
  [[nodiscard("Error value must be obtained")]] auto init(
      uint16_t width = DEFAULT_WIDTH, uint16_t height = DEFAULT_HEIGHT,
      uint32_t pixformat = DEFAULT_PIXFORMAT) -> int8_t;

  /**
   * @brief Dequeue buffers, handle Capture and Re-enqueue buffer
   *
   * @param processImageCallback
   * @return int8_t 0 if no errors occured
   */
  [[nodiscard("Error value must be obtained")]] auto handleCapture(
      const std::function<void(const buffer_addr &)> &processImageCallback)
      const -> int8_t;
};

}  // namespace v4l2Capture

#endif  // V4L2_CAPTURE_INCLUDED
