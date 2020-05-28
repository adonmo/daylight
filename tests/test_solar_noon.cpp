#include "catch.hpp"
#include "common/constants.h"
#include "common/utils.hpp"
#include <libdaylight/Sunclock.hpp>

int const MINUTE = 60;

TEST_CASE("Solar noon time is calculated with reasonable values",
          "[solar_noon]") {
  Sunclock s(HYD_LAT, HYD_LNG, IST_TZ_OFFSET);

  SECTION("Hyderabad solar noon times are calculated resonably") {
    REQUIRE(s.solar_noon(datetime(2020, 5, 21, 14, 10, 35)) ==
            Approx(datetime(2020, 5, 21, 12, 12, 36)).margin(MINUTE));
  }
}
