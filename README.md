<p align="center" style="margin: 48px 0;">
    <img src="static/logo.png" width="300">
</p>

<p align="center">
    <a href="https://github.com/adonmo/daylight/actions">
        <img src="https://github.com/adonmo/daylight/workflows/Tests/badge.svg" alt="Tests Status">
    </a>
    <a href="https://github.com/adonmo/daylight/actions">
        <img src="https://github.com/adonmo/daylight/workflows/Style/badge.svg" alt="Code Style Checks Status">
    </a>
    <a href="https://codecov.io/gh/adonmo/daylight">
        <img src="https://codecov.io/gh/adonmo/daylight/branch/master/graph/badge.svg" alt="Code Coverage">
    </a>
    <a href="https://pypistats.org/packages/daylight">
        <img src="https://img.shields.io/pypi/dm/daylight.svg" alt="PyPI downloads">
    </a>
    <a href="https://github.com/adonmo/daylight/blob/master/LICENSE.txt">
        <img src="https://img.shields.io/github/license/adonmo/daylight.svg" alt="MIT License">
    </a>
</p>

daylight or libdaylight is a library which enables you to answer daylight related questions like:

- Irradiance - How bright is it outside, given a particular time and location?
- What is the time of sunrise/solarnoon/sunset, given a particular time and location?

libdaylight is written in modern C++ with bindings to python using [pybind11](https://github.com/pybind/pybind11).

daylight's python bindings provide vectorized functions - allowing for efficient analysis when dealing with lots of queries. At the same, this allows daylight to play well with established data science tooling like numpy and pandas.

The math used in this library is mostly based on [NOAA's solar calculations](https://www.esrl.noaa.gov/gmd/grad/solcalc/calcdetails.html), which were in turn based on ***Astronomical Algorithms***, by Jean Meeus. Also thanks to [this Python implementation](https://michelanders.blogspot.com/2010/12/calulating-sunrise-and-sunset-in-python.html) of these calculations by Michel Landers, which was a very useful reference while building this library.

⚠️ Currently this library is only tested for basic use cases. For any scientific-grade use cases, or for cases where precise values are needed - this library is not extensively tested, yet. Any contributions from that aspect would be greatly appreciated.

# Installation

## From [PyPI](https://pypi.org/project/daylight/)
```sh
$ pip install daylight
```

## From source
```sh
$ pip install git+https://github.com/adonmo/daylight
```

Note: This requires cmake and pybind11 to be installed on your system. If you're having trouble with pybind11, [try using a conda enviroment](https://github.com/pybind/pybind11/issues/1379#issuecomment-468933426) instead.

# Examples

The examples directory contains a real world usage of this library at [Adonmo](https://www.adonmo.com) - for its season and location independent brightness control mechanism: [Click here](/examples/adonmo-daylight-brightness-control.ipynb) to read it.

![Adonmo brightness control mechanism using daylight](/static/adonmo-daylight-brightness-control.png)

# Usage (Python)

```python
import datetime
import pytz

import daylight

def epoch(year, month, day, hour=0, minute=0, second=0, tz=pytz.UTC):
    return int(tz.localize(datetime.datetime(year, month, day, hour, minute, second)).timestamp())

tz = pytz.timezone("Asia/Kolkata")
tz_offset = tz.utcoffset(datetime.datetime.utcnow()).total_seconds() / 3600

# Example with GPS coords for Hyderabad, India, in Indian timezone (IST)
sun = daylight.Sunclock(17.3859, 78.4867, tz_offset)

# Know the daylight strength / ambient brightness level at a given time of day
# Below call returns 0.882753920406182
sun.irradiance(epoch(2020, 5, 21, 14, 10, 35, tz))

# Know the sunrise time for a given date
# Returns unix timestamp for 5:42 AM
sun.sunrise(epoch(2020, 5, 21, tz=tz))

# Know the solar noon time for a given date
# Returns unix timestamp for 12:12 PM
sun.solar_noon(epoch(2020, 5, 21, tz=tz))

# Know the sunset time for a given date
# Returns unix timestamp for 18:42 PM
sun.sunset(epoch(2020, 5, 21, tz=tz))

# daylight's functions are vectorized as well - which means you can compute results
# for multiple parameters efficiently, while playing well with libraries like numpy/pandas
# Returns [-0.56570521  0.28650605]
sun.irradiance([
    epoch(2020, 5, 21, 3, 0, 0, tz),
    epoch(2020, 5, 21, 7, 0, 0, tz),
])
```

Python API Reference and comparision with other libraries can be found on our docs: https://adonmo-daylight.readthedocs.io/en/latest/

# Usage (C)

libdaylight can also be used in C through the provided C API.

Here is an example code on how to do this:

```c
#include "daylight_c.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    struct Sunclock* s = newSunclock(17.3859, 78.4867, 5.5);
    time_t t_20200521141035 = 1590050435;
    double irradiance = Sunclock_irradiance(s, t_20200521141035);
    printf("%lf\n", irradiance);
    deleteSunclock(s);
}
```

Save the above file as main.c, and run the following commands to build and run it:

Note: Make sure daylight is [built](#building) first before running these commands.

```sh
$ gcc -I/<path_to_daylight>/capi -c main.c -o main.o
$ g++ -L/<path_to_daylight>/build/capi main.o -l:libdaylight_c-0.1.1.so -o main
$ LD_LIBRARY_PATH=/<path_to_daylight>/build/capi ./main
0.882754
```

# API Reference

Python: https://adonmo-daylight.readthedocs.io/en/latest/reference.html

C++: https://adonmo.github.io/daylight/

# Development

libdaylight uses the [CMake](https://cmake.org/) build system.

## Building just the library

```sh
$ cmake -B build -S .
$ cmake --build build
```

This builds a static library file `libdaylight.a`

If you make any additional changes, you can just run `cmake --build build` again to get your changes reflected in the compiled outputs.

## Running tests

```sh
$ cmake -B build/test -S test
$ cmake --build build/test
$ ./build/test/libdaylight-tests
```
If everything is working okay, you should see "All tests passed".

libdaylight uses the [Catch2](https://github.com/catchorg/Catch2) library for its tests.

### Testing the python bindings

There are no strict tests yet for the python bindings. However you can run an example script file, making this a sanity test at least.

After building, from the tests/python directory, run:
```sh
$ python test.py
```
If everything is working okay, you should see "All tests passed".

## Building docs
### Python (Sphinx)

```sh
$ pip install sphinx sphinx_rtd_theme numpy numpydoc
$ cmake -B build/docs -S documentation
$ cmake --build build/docs
$ cmake --build build/docs --target pydocs
```
You can then proceed to host the docs locally, for example on http://0.0.0.0:8000/
```sh
$ python -m http.server --directory documentation/python/_build/html
```
### C++ (Doxygen)

```sh
$ cmake -B build/docs -S documentation
$ cmake --build build/docs
$ cmake --build build/docs --target cppdocs
```
You can then proceed to host the docs locally, for example on http://0.0.0.0:8000/
```sh
$ python -m http.server --directory build/docs/doxygen/html
```

## Contributing

Issues and pull requests are welcome.

* For proposing new features/improvements or reporting bugs, [create an issue](https://github.com/adonmo/daylight/issues/new/choose).
* Check [open issues](https://github.com/adonmo/daylight/issues) for viewing existing ideas, verify if it is already proposed/being worked upon.
* When implementing new features make sure to add relavant tests and documentation before sending pull requests.

## Related projects

[PyEphem](https://github.com/brandon-rhodes/pyephem), [pvlib-python](https://github.com/pvlib/pvlib-python) and [solarpy](https://github.com/aqreed/solarpy) are some libraries which have overlap with the type of problems this library solves.

Comparision between them and this library can be [read on our docs](https://adonmo-daylight.readthedocs.io/en/latest/similar-libraries.html)
