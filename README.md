# About

This is a C++ testing framework / library designed to have as little impact on compile times as possible. It makes extensive use of RAII both internally and externally to manage its state and provide some neat C++-oriented functionality (work in progress).

# Features and design goals

* Macro-free (API)
* Does not include any external or standard library headers in its own header files
* Supports most common assertions
* Supports checking RAII classes through `void_test::resource` class

# How to use (CMake projects)

This library can be used either as a subdirectory or as an installed CMake package. To install, run the following commands:

    git clone https://github.com/GDI512/void-test
    cd void-test
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
    cmake --build build --config Release
    cmake --install build (You may need to run this one with root privileges)

The `find_package (void-test)` command can be then used to access the exported target.

To add it to an existing CMake project without installing, just clone the repository into your source tree and use `add_subdirectory (void-test)`.

In both cases you will be able to link against it through the `void-test::voidtest` target.

# How to use (Other projects)

Run the following commands:

        git clone https://github.com/GDI512/void-test
        cd void-test
        cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
        cmake --build build --config Release

Then copy the include folder and the static library which should be somewhere in the build directory.

# Example

    #include <void_test.hpp>
    #include <vector>

    namespace test = void_test;

    int main() {

        test::unit("a test case", [](){

            test::unit("a nested test case", [](){

                auto vector = std::vector<int>();
                test::check_equal(vector.size(), 0u);
                test::check_equal(vector.capacity(), 0u);

            });

            test::unit("some other test case", [](){

                auto vector = std::vector<int>(256);
                test::check_equal(vector.size(), 256u);
                test::check_equal(vector.capacity(), 256u);
                vector.push_back(0);
                test::check_equal(vector.size(), 257u);
                test::check_greater(vector.capacity(), 257u);

            });

        });

        return test::exit_status();

    }

# Notes

* This library may go through some API-breaking changes before its first version is released. Proceed with caution!
* The documentation is ComingSoon™.
