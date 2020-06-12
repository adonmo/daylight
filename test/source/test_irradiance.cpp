#include <catch2/catch.hpp>
#include <daylight/Sunclock.hpp>
#include <tuple>

#include "common/constants.h"
#include "common/utils.hpp"

Sunclock HYD_SUN(HYD_LAT, HYD_LNG, IST_TZ_OFFSET);
Sunclock MUM_SUN(MUM_LAT, MUM_LNG, IST_TZ_OFFSET);

TEST_CASE("Irradiance is calculated with reasonable values", "[irradiance]") {
  SECTION("For the hyderabad location") {
    SECTION("Afternoons are pretty bright") {
      REQUIRE(HYD_SUN.irradiance(datetime(2020, 5, 21, 14, 10, 35))
              == Approx(0.8827526).epsilon(1e-4));
    }

    SECTION("Natural irradiance levels across various times of the day") {
      double expected;
      int y, mo, d, h, m, s;
      std::tie(y, mo, d, h, m, s, expected) = GENERATE(table<int, int, int, int, int, int, double>({
          {2020, 5, 21, 3, 0, 0, -0.5656889112210127},
          {2020, 5, 21, 7, 0, 0, 0.2865167778771277},
          {2020, 5, 21, 9, 30, 0, 0.7826009844055087},
          {2020, 5, 21, 12, 0, 0, 0.9975338749244066},
          {2020, 5, 21, 16, 0, 0, 0.5928553873758027},
          {2020, 5, 21, 18, 0, 0, 0.1522017192394623},
          {2020, 5, 21, 21, 0, 0, -0.4945949325413322},
          {2020, 5, 21, 23, 59, 59, -0.7912060752046477},
      }));
      REQUIRE(HYD_SUN.irradiance(datetime(y, mo, d, h, m, s)) == Approx(expected).epsilon(1e-4));
    }

    SECTION("Summer evenings are brighter than winter evenings") {
      double expected;
      int y, mo, d, h, m, s;
      std::tie(y, mo, d, h, m, s, expected) = GENERATE(table<int, int, int, int, int, int, double>({
          {2020, 6, 21, 19, 0, 0, -0.0416245},
          {2019, 12, 21, 19, 0, 0, -0.2951196},
      }));
      REQUIRE(HYD_SUN.irradiance(datetime(y, mo, d, h, m, s)) == Approx(expected).epsilon(1e-4));
    }

    SECTION("Same time across timezones give same values") {
      double tz, expected;
      int y, mo, d, h, m, s;
      std::tie(tz, y, mo, d, h, m, s, expected)
          = GENERATE(table<double, int, int, int, int, int, int, double>({
              {IST_TZ_OFFSET, 2020, 5, 21, 19, 0, 0, -0.0809624},
              {UTC_TZ_OFFSET, 2020, 5, 21, 13, 30, 0, -0.0809624},
          }));
      Sunclock sun(HYD_LAT, HYD_LNG, tz);
      int offset = (int)(tz * 60 * 60);
      REQUIRE(sun.irradiance(datetime(y, mo, d, h, m, s, offset))
              == Approx(expected).epsilon(1e-4));
    }

    SECTION("Measurement in different timezones give different values") {
      double tz, expected;
      int y, mo, d, h, m, s;
      std::tie(tz, y, mo, d, h, m, s, expected)
          = GENERATE(table<double, int, int, int, int, int, int, double>({
              {IST_TZ_OFFSET, 2020, 5, 21, 9, 0, 0, 0.700560},
              {UTC_TZ_OFFSET, 2020, 5, 21, 9, 0, 0, 0.842625},
          }));
      Sunclock sun(HYD_LAT, HYD_LNG, tz);
      int offset = (int)(tz * 60 * 60);
      REQUIRE(sun.irradiance(datetime(y, mo, d, h, m, s, offset))
              == Approx(expected).epsilon(1e-4));
    }
  }

  SECTION("Hyderabad vs Mumbai") {
    SECTION("For a fixed time, Hyderabad mornings are brighter than Mumbai") {
      // This is because Hyd is towards east, and sun rises in the east
      Sunclock *sun;
      double expected;
      int y, mo, d, h, m, s;
      std::tie(sun, y, mo, d, h, m, s, expected)
          = GENERATE(table<Sunclock *, int, int, int, int, int, int, double>({
              {&HYD_SUN, 2020, 5, 21, 9, 0, 0, 0.700560},
              {&MUM_SUN, 2020, 5, 21, 9, 0, 0, 0.636913},
          }));
      REQUIRE(sun->irradiance(datetime(y, mo, d, h, m, s)) == Approx(expected).epsilon(1e-4));
    }

    SECTION("For a fixed time, Mumbai evenings are brighter than Hyderabad") {
      // This is because Mum is towards west, and sun sets in the west
      Sunclock *sun;
      double expected;
      int y, mo, d, h, m, s;
      std::tie(sun, y, mo, d, h, m, s, expected)
          = GENERATE(table<Sunclock *, int, int, int, int, int, int, double>({
              {&MUM_SUN, 2020, 5, 21, 19, 0, 0, 0.016219982},
              {&HYD_SUN, 2020, 5, 21, 19, 0, 0, -0.0809624},
          }));
      REQUIRE(sun->irradiance(datetime(y, mo, d, h, m, s)) == Approx(expected).epsilon(1e-4));
    }
  }
}
