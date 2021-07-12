[![Windows Build](https://github.com/GDI512/citrine/actions/workflows/windows-ci.yml/badge.svg)](https://github.com/GDI512/citrine/actions/workflows/windows-ci.yml)
[![MacOS Build](https://github.com/GDI512/citrine/actions/workflows/macos-ci.yml/badge.svg)](https://github.com/GDI512/citrine/actions/workflows/macos-ci.yml)
[![Linux Build](https://github.com/GDI512/citrine/actions/workflows/linux-ci.yml/badge.svg)](https://github.com/GDI512/citrine/actions/workflows/linux-ci.yml)

# About
*Citrine* is a macro-free unit testing library designed for testing small projects.
It guarantees fast compile times by removing all standard library dependencies
from its header files and defines its own main function, making it very easy to use.

# Getting started
*Citrine* is meant to be used with CMake

    git clone https://github.com/GDI512/citrine.git
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
    cmake --build build --config Release
    cd build && ctest -C Release

If anything goes wrong during the build, please create an issue. Otherwise you have two
options:
* Copy the header files and the compiled library, then deal with linking
  and other options manually
* (Recommended) Delete the build directory and copy the files somewhere into the
  source tree of your CMake project. You can also use `git submodule add` to add
  this repository to your own or copy a zip with a specific version from the
  "Releases" section - in any case, after calling `add_subdirectory()` with the
  correct path, *Citrine* will define an alias target `citrine::citrine` which you
  will be able to use alongside the `add_executable()` and `target_link_libraries()`
  commands to easily define tests.
