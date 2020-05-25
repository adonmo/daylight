#include "catch.hpp"
#include <ctime>
#include <libdaylight/Sunclock.hpp>

double const HYD_LAT = 17.3859;
double const HYD_LNG = 78.4867;

time_t datetime(int year = 1970, int month = 1, int day = 1, int hour = 0,
                int minute = 0, int second = 0) {
  time_t rawtime;
  time(&rawtime);
  struct tm *timeinfo = gmtime(&rawtime);
  timeinfo->tm_year = year;
  timeinfo->tm_mon = month - 1;
  timeinfo->tm_mday = day;
  timeinfo->tm_hour = hour;
  timeinfo->tm_min = minute;
  timeinfo->tm_sec = second;
  return mktime(timeinfo);
}

TEST_CASE("Irradiance is calculated with reasonable values") {
  Sunclock s(HYD_LAT, HYD_LNG);

  SECTION("Hyderabad afternoons are pretty bright") {
    REQUIRE(s.irradiance(datetime(2020, 5, 21, 14, 10, 35)) ==
            Approx(0.8827526).epsilon(1e-4));
  }
}
