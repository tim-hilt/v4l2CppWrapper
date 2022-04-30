#include "utils.hpp"

#include <fmt/format.h>

#include <iomanip>
#include <sstream>

auto utils::formatHex(uint32_t s) -> std::string {
  return fmt::format("{:#010x}", s);
}
