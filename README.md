daylight
====

daylight or libdaylight is a library which enables you to answer daylight related questions like:

- Irradiance - How bright is it outside, given a particular time and location?
- What is the time of sunrise/solarnoon/sunset, given a particular time and location?

libdaylight is written in modern C++ with bindings to python using [pybind11](https://github.com/pybind/pybind11).

⚠️ Currently this library is only tested for basic use cases. For any scientific-grade use cases, or for cases where precise values are needed - this library is not extensively tested, yet. Any contributions from that aspect would be greatly appreciated.

# Installation

The package can be installed by running:

```sh
$ pip install git+https://github.com/adonmo/daylight
```

# Usage (Python)

```python
import datetime
import pytz

import daylight

def epoch(year, month, day, hour=0, minute=0, second=0):
    return int(datetime.datetime(year, month, day, hour, minute, second).replace(tzinfo=pytz.UTC).timestamp() * 1000)


# Example with GPS coords for Hyderabad, India
sun = daylight.Sunclock(17.3859, 78.4867)
sun.irradiance(epoch(2020, 5, 21, 14, 10, 35))
```
This should output:
```
0.8827526
```

# Development

## Building

libdaylight uses the [CMake](https://cmake.org/) build system. Follow these steps to build the project:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
```

This builds three artifacts:
 - **libdaylight&#46;so** - the compiled shared object for use in C/C++ projects.
 - **libdaylight-tests** - executable to run tests.
 - **daylight.cpython-38m-x86_64-linux-gnu.so** - python module bindings.

If you make any additional changes, you can just run `make` to get your changes reflected in the compiled outputs.

## Running tests

After building, from the build directory, run:
```sh
$ ./tests/libdaylight-tests
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
