#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <daylight/Sunclock.hpp>

namespace py = pybind11;

PYBIND11_MODULE(daylight, m) {
  py::class_<Sunclock>(m, "Sunclock")

      .def(py::init<double const &, double const &, double const &>(),
           R"pbdoc(
    Constructs a Sunclock object

    Parameters
    ----------
    latitude : float
        latitude of the location
    longitude : float
        longitude of the location
    tz_offset : float
        in hours, east is positive. i.e. IST is +5.5
)pbdoc",
           py::arg("latitude"), py::arg("longitude"), py::arg("tz_offset") = 0)

      .def("irradiance", py::vectorize((double (Sunclock::*)(time_t)) & Sunclock::irradiance),
           R"pbdoc(
    Calculates the irradiance level for given datetime.

    This is a vectorized function.

    Parameters
    ----------
    datetime : int or array_like
        unix timestamp (in UTC, seconds)

    Examples
    --------
    >>> import daylight
    >>> sun = daylight.Sunclock(17.3859, 78.4867, 5.5)
    >>> sun.irradiance(1590050435)
    0.882753920406182
    >>> sun.irradiance([1590010200, 1590024600])
    array([-0.56570521,  0.28650605])
)pbdoc",
           py::arg("datetime"))

      .def("sunrise", py::vectorize((time_t(Sunclock::*)(time_t)) & Sunclock::sunrise),
           R"pbdoc(
    Calculates the sunrise time for given date.

    This is a vectorized function.

    Parameters
    ----------
    date : int or array_like
        unix timestamp (in UTC, seconds)

    Examples
    --------
    >>> import daylight
    >>> sun = daylight.Sunclock(17.3859, 78.4867, 5.5)
    >>> sun.sunrise(1589999400)
    1590019961
    >>> sun.sunrise([1590010200, 1590024600])
    array([1590019959, 1590019957])
)pbdoc",
           py::arg("date"))

      .def("solar_noon", py::vectorize((time_t(Sunclock::*)(time_t)) & Sunclock::solar_noon),
           R"pbdoc(
    Calculates the solar noon time for given date.

    This is a vectorized function.

    Parameters
    ----------
    date : int or array_like
        unix timestamp (in UTC, seconds)

    Examples
    --------
    >>> import daylight
    >>> sun = daylight.Sunclock(17.3859, 78.4867, 5.5)
    >>> sun.solar_noon(1589999400)
    1590043354
    >>> sun.solar_noon([1590010200, 1590024600])
    array([1590043355, 1590043355])
)pbdoc",
           py::arg("date"))

      .def("sunset", py::vectorize((time_t(Sunclock::*)(time_t)) & Sunclock::sunset),
           R"pbdoc(
    Calculates the sunset time for given date.

    This is a vectorized function.

    Parameters
    ----------
    date : int or array_like
        unix timestamp (in UTC, seconds)

    Examples
    --------
    >>> import daylight
    >>> sun = daylight.Sunclock(17.3859, 78.4867, 5.5)
    >>> sun.sunset(1589999400)
    1590066748
    >>> sun.sunset([1590010200, 1590024600])
    array([1590066751, 1590066754])
)pbdoc",
           py::arg("date"));
}
