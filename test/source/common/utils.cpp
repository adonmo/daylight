#include "utils.hpp"

time_t datetime(int year, int month, int day, int hour, int minute, int second,
                int tz_offset) {
  struct std::tm epoch;
  epoch.tm_isdst = 0;
  epoch.tm_sec = epoch.tm_min = epoch.tm_hour = epoch.tm_mon = 0;
  epoch.tm_mday = 1;
  epoch.tm_year = 70;
  time_t local_tz_offset = mktime(&epoch);

  struct tm timeinfo = {};
  timeinfo.tm_year = year - 1900;
  timeinfo.tm_mon = month - 1;
  timeinfo.tm_mday = day;
  timeinfo.tm_hour = hour;
  timeinfo.tm_min = minute;
  timeinfo.tm_sec = second;
  return mktime(&timeinfo) - local_tz_offset - tz_offset;
}
