import platform
from setuptools import setup, Extension
from tools.write_version_info import get_version_info


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
    ext_modules=[
        Extension(
            'daylight',
            ['source/Sunclock.cpp', 'pybind/source/daylight.cpp'],
            include_dirs=[
                'include',
                'pybind/include',
                PyBind11Include(),
            ],
            extra_compile_args=extra_compile_args,
            language='c++',
        ),
    ],
    setup_requires=['pybind11~=2.5'],
    install_requires=["numpy"],
    extras_require={"docs": ["sphinx", "sphinx-rtd-theme", "numpydoc"]},
    zip_safe=False,
)
