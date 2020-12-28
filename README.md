# About
This is a C++ testing framework / library designed to have as little impact on compile times as possible. It makes extensive use of RAII both internally and externally to manage its state and provide some neat C++-oriented functionality (work in progress).

# Features and design goals
* Macro-free (mostly)
* Fast to compile
* Does not include any external or standard library headers in its own header files
* Supports most common assertions
* Supports checking RAII classes through `test::resource` class
* Just Works™ (Hopefully™)

# How to

## Build
Run the following commands then copy the library file and the include folder somewhere.

    git clone https://github.com/GDI512/void-test
    cd void-test
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
    cmake --build build --config Release

## Use
Make sure `void_test.hpp` is in your include path and you are linking your executable against the library.

    #include <void_test.hpp>
    #include <vector>

    VOID_TEST_BEGIN

    test::unit("a test unit", [](){

        test::unit("a nested unit", [](){

            auto vector = std::vector<int>();
            test::assert_equal(vector.size(), 0u);
            test::assert_equal(vector.capacity(), 0u);

        });

        test::unit("some other unit", [](){

            auto vector = std::vector<int>(256);
            test::assert_equal(vector.size(), 256u);
            test::assert_equal(vector.capacity(), 256u);
            vector.push_back(0);
            test::assert_equal(vector.size(), 257u);
            test::assert_greater(vector.capacity(), 257u);

        });

    });

    VOID_TEST_END

You get the idea.

# Notes

This library probably should not be used in its current state as it lacks a proper documentation and it may go through some API-breaking changes in the near future. Proceed with caution!
