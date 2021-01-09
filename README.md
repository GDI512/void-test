# About

This is a C++ testing framework / library designed to have as little impact on compile times as possible. It makes extensive use of RAII both internally and externally to manage its state and provide some neat C++-oriented functionality.

# Features and design goals

* Macro-free (API)
* Does not include any external or standard library headers in its own header files
* Supports most common assertions
* Supports checking RAII classes through `void_test::resource`

# How to use

This library can be used either as a subdirectory or as an installed CMake package. To install, run the following commands:

    git clone https://github.com/GDI512/void-test
    cd void-test
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
    cmake --build build --config Release
    cmake --install build

The `find_package (void-test)` command can be then used to access the exported target.

To add it to an existing CMake project without installing, just clone the repository into your source tree and use `add_subdirectory (void-test)`.

In both cases you will be able to link against it through the `void-test::void-test` target.

For more information, see [wiki](https://github.com/GDI512/void-test/wiki).

# Example

    #include <void_test.hpp>
    #include <stdexcept>
    #include <vector>

    namespace test = void_test;

    int main() {

        test::unit("main-unit", [](){

            test::unit("nested-unit", [](){
                auto vec = std::vector<int>();
                test::check_equal(vec.size(), 0u);
                test::check_equal(vec.capacity(), 0u);
            });

            test::unit("some-other-unit", [](){
                auto vec = std::vector<int>(256);
                test::check_equal(vec.size(), 256u);
                test::check_equal(vec.capacity(), 256u);
                vec.push_back(0);
                test::check_equal(vec.size(), 257u);
                test::check_greater(vec.capacity(), 257u);
            });

            test::unit("failing-unit", [](){
                test::check(false);
                test::check_not_less(32, 64);
                test::check_throws([](){ return 0; });
            });

            test::unit("unhandled-exception-unit", [](){
                throw std::exception();
            });

        });

        return test::exit_status();

    }

The code above will produce the following output (in color):

    (unit main-unit)
        (unit nested-unit)
            (ok check_equal)
            (ok check_equal)
            (unit ok [0/2])
        (unit some-other-unit)
            (ok check_equal)
            (ok check_equal)
            (ok check_equal)
            (ok check_greater)
            (unit ok [0/4])
        (unit failing-unit)
            (error check)
            (error check_not_less)
            (error check_throws)
            (unit error [3/3])
        (unit unhandled-exception-unit)
            (unhandled exception unhandled-exception-unit)
            (unit error [1/1])

# Notes

* This library may go through some API-breaking changes before its first version is released. Proceed with caution!
