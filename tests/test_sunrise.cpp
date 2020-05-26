#include "catch.hpp"
#include "common/constants.h"
#include "common/utils.hpp"
#include <libdaylight/Sunclock.hpp>

int const MINUTE = 60;

TEST_CASE("Sunrise time is calculated with reasonable values", "[sunrise]") {
  Sunclock s(HYD_LAT, HYD_LNG);

  SECTION("Hyderabad sunrise times are calculated resonably") {
    REQUIRE(s.sunrise(datetime(2020, 5, 21, 14, 10, 35)) ==
            Approx(datetime(2020, 5, 21, 0, 12, 29)).margin(MINUTE));
  }
}
