#include "utils.hpp"

#include <iomanip>
#include <sstream>

constexpr uint8_t HEX_WIDTH{8};

auto utils::printHex(uint32_t s) -> std::string {
  std::stringstream ss;
  ss << "0x" << std::setfill('0') << std::setw(HEX_WIDTH) << std::right
     << std::hex << s;
  return ss.str();
}
