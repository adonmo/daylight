#include <libdaylight/Sunclock.hpp>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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

      .def("irradiance",
           py::vectorize((double (Sunclock::*)(time_t)) & Sunclock::irradiance),
           R"pbdoc(
    Calculates the irradiance level for given date.

    Parameters
    ----------
    date : int
        unix timestamp (in UTC, seconds)

    Examples
    --------
    >>> import daylight
    >>> sun = daylight.Sunclock(17.3859, 78.4867, 5.5)
    >>> sun.irradiance(1590050435)
    0.882753920406182
)pbdoc",
           py::arg("date"))

      .def("sunrise",
           py::vectorize((time_t(Sunclock::*)(time_t)) & Sunclock::sunrise),
           R"pbdoc(
    Calculates the sunrise time for given date.

    Parameters
    ----------
    date : int
        unix timestamp (in UTC, seconds)

    Examples
    --------
    >>> import daylight
    >>> sun = daylight.Sunclock(17.3859, 78.4867, 5.5)
    >>> sun.sunrise(1589999400)
    1590019961
)pbdoc",
           py::arg("date"))

      .def("solar_noon",
           py::vectorize((time_t(Sunclock::*)(time_t)) & Sunclock::solar_noon),
           R"pbdoc(
    Calculates the solar noon time for given date.

    Parameters
    ----------
    date : int
        unix timestamp (in UTC, seconds)

    Examples
    --------
    >>> import daylight
    >>> sun = daylight.Sunclock(17.3859, 78.4867, 5.5)
    >>> sun.solar_noon(1589999400)
    1590043354
)pbdoc",
           py::arg("date"))

      .def("sunset",
           py::vectorize((time_t(Sunclock::*)(time_t)) & Sunclock::sunset),
           R"pbdoc(
    Calculates the sunset time for given date.

    Parameters
    ----------
    date : int
        unix timestamp (in UTC, seconds)

    Examples
    --------
    >>> import daylight
    >>> sun = daylight.Sunclock(17.3859, 78.4867, 5.5)
    >>> sun.sunset(1589999400)
    1590066748
)pbdoc",
           py::arg("date"));
}
