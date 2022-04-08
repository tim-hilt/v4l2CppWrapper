#include <vector>

#include <v4l2_capture.hpp>

int main() {
  int test = 5;
  std::size_t t = 0;
  std::vector<bool> vec = std::vector<bool>();
  vec.emplace_back(true);
  v4l2Capture::say_hello();
}