#ifndef __DAYLIGHT_H
#define __DAYLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#include <daylight/Sunclock.hpp>

typedef struct Sunclock Sunclock;

Sunclock *newSunclock(double const latitude_, double const longitude_, double const tz_offset_);

double Sunclock_irradiance(Sunclock *v, time_t when);
time_t Sunclock_sunrise(Sunclock *v, time_t date);
time_t Sunclock_solar_noon(Sunclock *v, time_t date);
time_t Sunclock_sunset(Sunclock *v, time_t date);

void deleteSunclock(Sunclock *v);

#ifdef __cplusplus
}
#endif
#endif