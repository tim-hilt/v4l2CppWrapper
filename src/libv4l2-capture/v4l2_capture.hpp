#ifndef V4L2_CAPTURE_INCLUDED
#define V4L2_CAPTURE_INCLUDED

namespace v4l2Capture {

/**
 * @brief Opens a video device
 *
 */
void openVideoDevice();

/**
 * @brief Closes a video device
 *
 */
void closeVideoDevice();

/**
 * @brief Send ioctl commands to the display driver
 *
 */
void ioctl();

/**
 * @brief Memory map a driver-allocated buffer to userspace
 *
 */
void mmap();

/**
 * @brief Read frame from video device
 *
 */
void readFrame();

} // namespace v4l2Capture

#endif // V4L2_CAPTURE_INCLUDED