[![Windows Build](https://github.com/GDI512/cppltf/actions/workflows/windows-ci.yml/badge.svg)](https://github.com/GDI512/cppltf/actions/workflows/windows-ci.yml)
[![MacOS Build](https://github.com/GDI512/cppltf/actions/workflows/macos-ci.yml/badge.svg)](https://github.com/GDI512/cppltf/actions/workflows/macos-ci.yml)
[![Linux Build](https://github.com/GDI512/cppltf/actions/workflows/linux-ci.yml/badge.svg)](https://github.com/GDI512/cppltf/actions/workflows/linux-ci.yml)
# About
The *Lightweight C++ Testing Framework* is a modern macro-free library designed
for testing small projects. It guarantees fast compile times by removing all
standard headers from its own header files and precompiling all of the
implementation details into a static library.

Because *cppltf* defines its own main function, it is very easy to use and
does not require more setup than what can be seen in the example below.

```c++
#include <cppltf.hpp>

const auto group = test::unit("raii", []{

    test::unit("test::counter", []{
        auto vector = std::vector<test::counter>(64);
        test::check_equal(vector.size(), 64);
        test::check_equal(vector.capacity(), 64);
    });

    test::unit("test::vector", []{
        auto vector = std::vector<test::object>(64);
        test::check_equal(vector.size(), 64);
        test::check_equal(vector.capacity(), 64);
        vector.insert(vector.begin() + 4, 1);
        test::check(vector[4] == 1);
        test::check_equal(vector.size(), 65);
        test::check_greater(vector.capacity(), 65);
    });

});
```

To learn more about using this library, look into the *example* directory. The
examples there contain code and comments which explain all API features.

# Getting started
To build and test *cppltf* (assuming you installed CMake on your machine),
simply run the following commands:

    git clone https://github.com/GDI512/cppltf.git
    cmake -S . -B build -D CMAKE_BUILD_TYPE=RelWithDebInfo
    cmake --build build --config RelWithDebInfo
    cd build && ctest -C RelWithDebInfo

If anything goes wrong, please report an issue on Github. Otherwise you have two
options:
* Copy the *include* directory and the compiled library, then deal with linking
  and other compiler options manually
* (Recommended) Delete the build directory and copy the files somewhere into the
  source tree of your CMake project. You can also use `git submodule add` to add
  this repository to your own or copy a zip with a specific version from the
  "Releases" section - in any case, after calling `add_subdirectory()` with the
  correct path, *cppltf* will define an alias target `cppltf::cppltf` which you
  will be able to use alongside the `add_executable()` and
  `target_link_libraries()` commands to easily define tests.
