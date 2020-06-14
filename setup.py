import os
import re
import sys
import platform
import subprocess

from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext
from distutils.version import LooseVersion

from tools.write_version_info import get_version_info


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir='', **kwargs):
        Extension.__init__(self, name, **kwargs)
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)', out.decode()).group(1))
        if cmake_version < LooseVersion('3.14.0'):
            raise RuntimeError("CMake >= 3.14.0 is required")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        build_type = os.environ.get("BUILD_TYPE", "Release")
        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable]
        cmake_args += ['-DCMAKE_BUILD_TYPE=' + build_type]

        build_args = ['--config', build_type]
        build_args += ['--', '-j4']

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', '-B', self.build_temp, '-S', ext.sourcedir + os.sep + 'pybind'] + cmake_args)
        subprocess.check_call(['cmake', '--build', self.build_temp] + build_args)

setup(
    name='daylight',
    version=get_version_info()[3],
    author='Krishna Chaitanya Bommakanti',
    author_email='bkchaitan94@gmail.com',
    description='Python bindings to libdaylight',
    long_description=open("README.md", encoding="utf-8").read(),
    long_description_content_type='text/markdown',
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Operating System :: OS Independent",
        "Programming Language :: C",
        "Programming Language :: C++",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Intended Audience :: Developers",
        "Intended Audience :: Education",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: MIT License",
        "Natural Language :: English",
        "Topic :: Home Automation",
        "Topic :: Scientific/Engineering :: GIS",
        "Topic :: Utilities",
    ],
    keywords='irradiance sunrise sunset sun geo gis',
    ext_modules=[CMakeExtension('daylight', sources=[])],
    packages=find_packages(),
    install_requires=["numpy"],
    extras_require={"docs": ["sphinx", "sphinx-rtd-theme", "numpydoc"]},
    cmdclass=dict(build_ext=CMakeBuild),
    url="https://github.com/adonmo/daylight",
    zip_safe=False
)
