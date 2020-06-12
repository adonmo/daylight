#include <catch2/catch.hpp>
#include <daylight/Sunclock.hpp>

#include "common/constants.h"
#include "common/utils.hpp"

int const MINUTE = 60;

TEST_CASE("Sunset time is calculated with reasonable values", "[sunset]") {
  Sunclock s(HYD_LAT, HYD_LNG, IST_TZ_OFFSET);

  SECTION("Hyderabad sunset times are calculated resonably") {
    REQUIRE(s.sunset(datetime(2020, 5, 21, 14, 10, 35))
            == Approx(datetime(2020, 5, 21, 18, 42, 41)).margin(MINUTE).epsilon(0));
  }
}
