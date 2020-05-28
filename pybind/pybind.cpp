#include <libdaylight/Sunclock.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(daylight, m) {
  py::class_<Sunclock>(m, "Sunclock")
      .def(py::init<double const &, double const &, double const &>(),
           "Constructs a Sunclock object", py::arg("latitude_"),
           py::arg("longitude_"), py::arg("tz_offset_") = 0)
      .def("irradiance", (double (Sunclock::*)()) & Sunclock::irradiance)
      .def("irradiance", (double (Sunclock::*)(time_t)) & Sunclock::irradiance)
      .def("sunrise", (time_t(Sunclock::*)()) & Sunclock::sunrise)
      .def("sunrise", (time_t(Sunclock::*)(time_t)) & Sunclock::sunrise)
      .def("solar_noon", (time_t(Sunclock::*)()) & Sunclock::solar_noon)
      .def("solar_noon", (time_t(Sunclock::*)(time_t)) & Sunclock::solar_noon)
      .def("sunset", (time_t(Sunclock::*)()) & Sunclock::sunset)
      .def("sunset", (time_t(Sunclock::*)(time_t)) & Sunclock::sunset);
}
