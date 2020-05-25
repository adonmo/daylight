#ifndef DAYLIGHT_SUNCLOCK_HPP
#define DAYLIGHT_SUNCLOCK_HPP

#include <ctime>

class Sunclock {
public:
  Sunclock(double const &latitude_, double const &longitude_);

  /**
   * \overload double Sunclock::irradiance(time_t const &when)
   */
  double irradiance();

  /**
   * Specifically, we calculate Direct Normal Irradiance
   * That is we do not consider atmospheric components like cloud cover,
   * moisture content etc.
   *
   * @param when
   * @return a value representing irradiance (power per unit area)
   */
  double irradiance(time_t const &when);

private:
  // in decimal degrees, east is positive
  double const latitude;

  // in decimal degrees, north is positive
  double const longitude;

  // percentage past midnight, i.e. noon  is 0.5
  double time_of_day;

  // in hours, east is positive, i.e. IST (+05:30) is 5.5
  double timezone;

  static int days_since_1900(struct tm *t);

  /**
   * Get day count since Monday, January 1, 4713 BC
   * https://en.wikipedia.org/wiki/Julian_day
   *
   * @param t
   * @param time_of_day percentage past midnight, i.e. noon is 0.5
   * @param timezone    in hours, i.e. IST (+05:30) is 5.5
   * @return julian day
   */
  static double julian_day(struct tm *t, double const &time_of_day,
                           double const &timezone);

  /**
   * Extract information in a suitable format from a time_t object.
   */
  void prepare_time(time_t const &when, struct tm *ptm);

  /**
   * Performs the actual calculations.
   */
  double calculate_irradiance(struct tm *t);
};

#endif
