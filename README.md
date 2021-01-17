# About
This is a lightweight C++ testing framework designed to have minimal impact on compile times. It does not rely on macros and is very easy to integrate into other projects.

# Features
* **Macro-free** - There are no assertion or test case macros, instead, this framework makes extensive use of C++11 lambdas and templates to achieve similar functionality.
* **Fast** - The header files do not include any system headers or other external dependencies to minimize impact on compile times. All code which can and should be precompiled is compiled into a static library.
* **Easy to use** - Everything from building to writing tests is as straightforward as possible. At least by C++ standards.

# Building
Run the following commands:

    git clone https://github.com/GDI512/void-test.git
    cd void-test
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
    cmake --build build --config Release

It is highly recommended to run the tests too:

    cd build
    ctest
    cd ..

# Installing
The easiest way of adding `void-test` to a project is to just install it. Run the following command as an administrator / root after going through the previous section:

    cmake --install build

Then add the following line to a top-level *CMakeLists.txt* file to make the exported `void-test::void-test` target available:

```cmake
find_package (void-test REQUIRED)
```

# Building as a subdirectory
If installing is not an option simply clone the repository and move it somewhere into the project's source tree. This library defines an alias target (called `void-test::void-test` too) when built as a subdirectory. Given this hypothetical project structure:

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

Adding the following line to *external/CMakeLists.txt* will make it accessible:

```cmake
add_subdirectory (void-test)
```

# Example
> Disclaimer: I have not checked if this is actually how an `std::vector` is supposed to behave.

```c++
#include <void_test.hpp>
#include <vector>

namespace vt = void_test;

auto test = vt::unit("vector-test", [](){

    vt::unit("constructor-test", [](){

        vt::unit("default-constructor", [](){
            auto vector = std::vector<int>();
            vt::check(vector.empty());
            vt::check_equal(vector.capacity(), 0);
        });

        vt::unit("fill-constructor", [](){
            auto vector = std::vector<int>(32, 8);
            vt::check(!vector.empty());
            vt::check_equal(vector.size(), 32);
            vt::check_not_less(vector.capacity(), 32);
        });

    });

    vt::unit("modifier-test", [](){

        vt::unit("emplace", [](){
            auto vector = std::vector<int>(32, 8);
            vector.emplace(vector.begin() + 1, 4);
            vt::check(vector[1] == 4);
            vt::check_equal(vector.size(), 33);
            vt::check_greater(vector.capacity(), 33);
        });

        vt::unit("emplace_back", [](){
            auto vector = std::vector<int>(32, 8);
            vector.emplace_back(4);
            vt::check(vector.back() == 4);
            vt::check_equal(vector.size(), 33);
            vt::check_greater(vector.capacity(), 33);
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
