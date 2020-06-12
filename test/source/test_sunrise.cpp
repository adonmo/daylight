#include <catch2/catch.hpp>
#include <daylight/Sunclock.hpp>

#include "common/constants.h"
#include "common/utils.hpp"

int const MINUTE = 60;

TEST_CASE("Sunrise time is calculated with reasonable values", "[sunrise]") {
  Sunclock s(HYD_LAT, HYD_LNG, IST_TZ_OFFSET);

  SECTION("Hyderabad sunrise times are calculated resonably") {
    REQUIRE(s.sunrise(datetime(2020, 5, 21, 14, 10, 35))
            == Approx(datetime(2020, 5, 21, 5, 42, 32)).margin(MINUTE).epsilon(0));
  }
}
