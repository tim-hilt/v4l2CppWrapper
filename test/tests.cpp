#include <catch.hpp>
#include <catch2/catch.hpp>
#include <cstdint>
#include <utils.hpp>
#include <v4l2_capture.hpp>

TEST_CASE("hex-formatting works as expected") {
  REQUIRE(utils::formatHex(42) == "0x0000002a");
}
