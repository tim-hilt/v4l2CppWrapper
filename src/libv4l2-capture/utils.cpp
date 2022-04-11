#include "utils.hpp"

#include <iomanip>
#include <sstream>

auto utils::printHex(std::uint32_t s) -> std::string {
  std::stringstream ss;
  ss << "0x" << std::setfill('0') << std::setw(8) << std::right << std::hex
     << s;
  return ss.str();
}