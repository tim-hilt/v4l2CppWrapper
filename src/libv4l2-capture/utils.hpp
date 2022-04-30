#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <cstdint>
#include <string>

namespace utils {
[[nodiscard]] auto formatHex(uint32_t s) -> std::string;
}  // namespace utils

#endif  // UTILS_INCLUDED
