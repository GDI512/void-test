# About
This is a lightweight C++ testing framework designed to have minimal impact on compile times. It does not rely on macros and is very easy to integrate into other CMake projects.

# Features
* **Macro-free** - There are no assertion or test case macros, instead, this framework makes extensive use of C++11 lambdas and templates to achieve similar functionality.
* **Fast to compile** - The header files do not include any system headers or other external dependencies to minimize impact on compile times. All code which can and should be precompiled is compiled into a static library.
* **Easy to use** - Everything from building to writing tests is as straightforward as possible. At least by C++ standards.

# Building
To build for use outside CMake, run the following commands:

    git clone https://github.com/GDI512/void-test.git
    cd void-test
    cmake -S . -B build -D CMAKE_BUILD_TYPE=RelWithDebInfo
    cmake --build build --config RelWithDebInfo

It is highly recommended to run the tests too:

    cd build
    ctest
    cd ..

# Adding to CMake projects
The easiest way of using *void-test* is to add it as a git submodule or just clone it into project's source tree, for example:

    external/
    |-void-test/
    |-CMakeLists.txt
    include/
    |- header.hpp
    |- ...
    source/
    |- src.cpp
    |- ...
    |- CMakeLists.txt
    CMakeLists.txt

Assuming *external* was added as a subdirectory itself, adding the following line to *external/CMakeLists.txt* will make the alias target `void-test::void-test` accessible:

```cmake
add_subdirectory (void-test)
```

Afterwards all you need to do is just add it as a dependency like you would do with any other CMake library:

```cmake
add_executable (<test-target>)
target_sources (<test-target> PRIVATE <source-file>)
target_link_libraries (<test-target> PRIVATE void-test::void-test)
```

Keep in mind that tests are disabled for subdirectory builds like this one. If you would like to test *void-test* on your machine, follow the procedure from previous section.

# Example
> Disclaimer: I have not checked if this is actually how an `std::vector` is supposed to behave.

```c++
#include <void_test.hpp>
#include <vector>

auto group = test::unit("vector-test", [](){

    test::unit("constructor-test", [](){

        test::unit("default-constructor", [](){
            auto vector = std::vector<int>();
            test::check(vector.empty());
            test::check_equal(vector.capacity(), 0);
        });

        test::unit("fill-constructor", [](){
            auto vector = std::vector<int>(32, 8);
            test::check(!vector.empty());
            test::check_equal(vector.size(), 32);
            test::check_not_less(vector.capacity(), 32);
        });

    });

    test::unit("modifier-test", [](){

        test::unit("emplace", [](){
            auto vector = std::vector<int>(32, 8);
            vector.emplace(vector.begin() + 1, 4);
            test::check(vector[1] == 4);
            test::check_equal(vector.size(), 33);
            test::check_greater(vector.capacity(), 33);
        });

        test::unit("emplace_back", [](){
            auto vector = std::vector<int>(32, 8);
            vector.emplace_back(4);
            test::check(vector.back() == 4);
            test::check_equal(vector.size(), 33);
            test::check_greater(vector.capacity(), 33);
        });

    });

});

```

The `void-test` library defines its own main function so the following code can be compiled to an executable as-is. Assuming everything went right except for the `emplace_back()` function which forgot to increase the capacity of the vector exponentially, the output will look like this (but in color):

    (unit constructor-test)
      (unit default-constructor)
        (ok check)
        (ok check_equal)
        (unit ok [0/2])
      (unit fill-constructor)
        (ok check)
        (ok check_equal)
        (ok check_not_less)
        (unit ok [0/3])
    (unit modifier-test)
      (unit emplace)
        (ok check)
        (ok check_equal)
        (ok check_greater)
        (unit ok [0/3])
      (unit emplace_back)
        (ok check)
        (ok check_equal)
        (error check_greater)
        (unit ok [0/3])

See [wiki](https://github.com/GDI512/void-test/wiki) for a tutorial and API reference.
