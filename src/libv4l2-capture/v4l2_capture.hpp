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
 * @brief Meta ioctl-wrapper, that retries the operation, if the system call was
 *        interrupted
 *
 * @param fh File handle on which to act
 * @param request ioctl command to execute
 * @param arg data-structure to read/write on
 * @return int whether or not execution was successful
 */
static int xioctl(int fh, int request, void *arg);

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