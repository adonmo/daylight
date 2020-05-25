#include <cmath>
#include <libdaylight/Sunclock.hpp>
#include <stdexcept>

inline double rad(double radians) {
  static const double pi_on_180 = 4.0 * atan(1.0) / 180.0;
  return radians / pi_on_180;
}

inline double deg(double degrees) {
  static const double pi_on_180 = 4.0 * atan(1.0) / 180.0;
  return degrees * pi_on_180;
}

Sunclock::Sunclock(double const &latitude_, double const &longitude_)
    : latitude(latitude_), longitude(longitude_) {}

double Sunclock::irradiance() { return irradiance(time(0)); }

double Sunclock::irradiance(time_t const &when) {
  struct tm *t = gmtime(&when);
  prepare_time(when, t);
  return calculate_irradiance(t);
}

void Sunclock::prepare_time(time_t const &when, struct tm *t) {
  time_of_day = (t->tm_hour + t->tm_min / 60.0 + t->tm_sec / 3600.0) / 24.0;

  double offset = t->tm_gmtoff;
  timezone = offset / 3600;
}

int Sunclock::days_since_1900(struct tm *t) {
  int year = t->tm_year;
  if (year < 1900 || year > 2099) {
    throw std::invalid_argument(
        "days_since_1900 - Date must be between 1900 and 2099");
  }
  year -= 1900;
  int month = t->tm_mon + 1;
  int days = t->tm_mday;

  if (month < 3) {
    month += 12;
    year--;
  }
  int yearDays = (int)(year * 365.25);
  int monthDays = (int)((month + 1) * 30.61);

  return (yearDays + monthDays + days - 63);
}

double Sunclock::julian_day(struct tm *t, double const &time_of_day,
                            double const &timezone) {
  return days_since_1900(t) + 2415018.5 + time_of_day - timezone / 24;
}

double Sunclock::calculate_irradiance(struct tm *t) {
  double jday = julian_day(t, time_of_day, timezone);
  double _julian_century = (jday - 2451545.0) / 36525.0;

  double _mean_anom_sun =
      357.52911 + _julian_century * (35999.05029 - 0.0001537 * _julian_century);
  double _mean_long_sun =
      (280.46646 +
       fmod(_julian_century * (36000.76983 + _julian_century * 0.0003032),
            360));
  double _eccent_earth_orbit =
      0.016708634 -
      _julian_century * (0.000042037 + 0.0001537 * _julian_century);
  double _mean_obliq_ecliptic =
      (23 +
       (26 +
        ((21.448 - _julian_century *
                       (46.815 + _julian_century *
                                     (0.00059 - _julian_century * 0.001813)))) /
            60) /
           60);
  double _obliq_corr = _mean_obliq_ecliptic +
                       0.00256 * cos(deg(125.04 - 1934.136 * _julian_century));
  double _var_y = tan(deg(_obliq_corr / 2)) * tan(deg(_obliq_corr / 2));
  double _sun_eq_of_centre =
      (sin(deg(_mean_anom_sun)) *
           (1.914602 -
            _julian_century * (0.004817 + 0.000014 * _julian_century)) +
       sin(deg(2 * _mean_anom_sun)) * (0.019993 - 0.000101 * _julian_century) +
       sin(deg(3 * _mean_anom_sun)) * 0.000289);
  double _sun_true_long = _mean_long_sun + _sun_eq_of_centre;
  double _sun_app_long =
      (_sun_true_long - 0.00569 -
       0.00478 * sin(deg(125.04 - 1934.136 * _julian_century)));
  double _declination =
      rad(asin(sin(deg(_obliq_corr)) * sin(deg(_sun_app_long))));

  double _eq_of_time =
      4 * rad(_var_y * sin(2 * deg(_mean_long_sun)) -
              2 * _eccent_earth_orbit * sin(deg(_mean_anom_sun)) +
              4 * _eccent_earth_orbit * _var_y * sin(deg(_mean_anom_sun)) *
                  cos(2 * deg(_mean_long_sun)) -
              0.5 * _var_y * _var_y * sin(4 * deg(_mean_long_sun)) -
              1.25 * _eccent_earth_orbit * _eccent_earth_orbit *
                  sin(2 * deg(_mean_anom_sun)));

  double _true_solar_time = fmod(
      (time_of_day * 1440 + _eq_of_time + 4 * longitude - 60 * timezone), 1440);
  double _hour_angle = (_true_solar_time / 4 < 0 ? _true_solar_time / 4 + 180
                                                 : _true_solar_time / 4 - 180);

  double _solar_zenith = rad(acos(sin(deg(latitude)) * sin(deg(_declination)) +
                                  cos(deg(latitude)) * cos(deg(_declination)) *
                                      cos(deg(_hour_angle))));

  double _solar_elevation = 90 - _solar_zenith;

  return std::sin(deg(_solar_elevation));
}
