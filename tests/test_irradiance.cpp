#include "catch.hpp"
#include "common/constants.h"
#include "common/utils.hpp"
#include <libdaylight/Sunclock.hpp>

TEST_CASE("Irradiance is calculated with reasonable values", "[irradiance]") {
  Sunclock s(HYD_LAT, HYD_LNG);

  SECTION("Hyderabad afternoons are pretty bright") {
    // this would be 14:10:35 in IST
    REQUIRE(s.irradiance(datetime(2020, 5, 21, 8, 50, 35)) ==
            Approx(0.8627683103975419).epsilon(1e-4));
  }
}
