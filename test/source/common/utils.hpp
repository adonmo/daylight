#ifndef LIBDAYLIGHT_TESTS_COMMON_UTILS_HPP
#define LIBDAYLIGHT_TESTS_COMMON_UTILS_HPP

#include "constants.h"
#include <ctime>

time_t datetime(int year = 1970, int month = 1, int day = 1, int hour = 0,
                int minute = 0, int second = 0,
                int offset = IST_TZ_OFFSET * 60 * 60);

#endif
