import platform
from setuptools import setup, Extension


class PyBind11Include:
    def __str__(self):
        import pybind11

        return pybind11.get_include()


extra_compile_args = []
if platform.system() == "Windows":
    extra_compile_args.append('/std:c++14')
else:
    extra_compile_args.append('-std=c++14')


setup(
    ext_modules=[
        Extension(
            'daylight',
            [
                'source/Sunclock.cpp',
                'pybind/source/daylight.cpp'
            ],
            include_dirs=[
                'include',
                'pybind/include',
                PyBind11Include(),
            ],
            extra_compile_args=extra_compile_args,
            language='c++',
        ),
    ],
)
