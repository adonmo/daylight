#include "catch.hpp"
#include "common/constants.h"
#include "common/utils.hpp"
#include <libdaylight/Sunclock.hpp>

int const MINUTE = 60;

TEST_CASE("Sunset time is calculated with reasonable values", "[sunset]") {
  Sunclock s(HYD_LAT, HYD_LNG);

  SECTION("Hyderabad sunset times are calculated resonably") {
    REQUIRE(s.sunset(datetime(2020, 5, 21, 14, 10, 35)) ==
            Approx(datetime(2020, 5, 21, 13, 12, 46)).margin(MINUTE));
  }
}
