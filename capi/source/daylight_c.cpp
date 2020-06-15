#include <daylight/daylight_c.h>

#include <daylight/Sunclock.hpp>

extern "C" {
Sunclock *newSunclock(double const latitude_, double const longitude_, double const tz_offset_) {
  return new Sunclock(latitude_, longitude_, tz_offset_);
}

double Sunclock_irradiance(Sunclock *s, time_t when) { return s->irradiance(when); }

time_t Sunclock_sunrise(Sunclock *s, time_t date) { return s->sunrise(date); }

time_t Sunclock_solar_noon(Sunclock *s, time_t date) { return s->solar_noon(date); }

time_t Sunclock_sunset(Sunclock *s, time_t date) { return s->sunset(date); }

void deleteSunclock(Sunclock *s) { delete s; }
}
