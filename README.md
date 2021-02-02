# About
This is a lightweight C++ testing framework designed to have minimal impact on compile times.
It does not rely on macros and is very easy to integrate into other CMake projects.
May go through some API-breaking changes in the future.

# Features
* **Macro-free** - There are no assertion or test case macros, instead, this framework makes extensive use of C++11 lambdas and templates to achieve similar functionality.
* **Fast to compile** - The header files do not include any system headers or other external dependencies to minimize impact on compile times. All code which can and should be precompiled is compiled into a static library.
* **Easy to use** - Everything from building to writing tests is as straightforward as possible. At least by C++ standards.

# Building
To build for use outside CMake, run the following commands:

    git clone https://github.com/GDI512/voidtest.git
    cd voidtest
    cmake -S . -B build -D CMAKE_BUILD_TYPE=RelWithDebInfo
    cmake --build build --config RelWithDebInfo

It is highly recommended to run the tests too:

    cd build
    ctest
    cd ..

# Adding to CMake projects
The easiest way of using *voidtest* is to add it as a git submodule or just clone it into project's source tree, for example:

    external/
    |-voidtest/
    |-CMakeLists.txt
    include/
    |- header.hpp
    |- ...
    source/
    |- src.cpp
    |- ...
    |- CMakeLists.txt
    CMakeLists.txt

Assuming *external* was added as a subdirectory itself, adding the following line to *external/CMakeLists.txt* will make the alias target `voidtest::voidtest` accessible:

```cmake
add_subdirectory (voidtest)
```

Afterwards all you need to do is just add it as a dependency like you would do with any other CMake library:

```cmake
add_executable (<test-target>)
target_sources (<test-target> PRIVATE <source-file>)
target_link_libraries (<test-target> PRIVATE voidtest::voidtest)
```

Keep in mind that tests are disabled for subdirectory builds like this one. If you would like to test *voidtest* on your machine, follow the procedure from previous section.

# How to use

See [wiki](https://github.com/GDI512/voidtest/wiki) for a tutorial and API reference.
