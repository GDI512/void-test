# About
This is a C++ testing framework / library designed to have as little impact on compile times as possible. It makes extensive use of RAII both internally and externally to manage its state and provide some neat C++-oriented functionality (work in progress).

# Features and design goals
* Macro-free (API)
* Does not include any external or standard library headers in its own header files
* Supports most common assertions
* Supports checking RAII classes through `void_test::resource` class
* 

# How to

## Build
Run the following commands:

    git clone https://github.com/GDI512/void-test
    cd void-test
    cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
    cmake --build build --config Release

## Use
Make sure `void_test.hpp` is in your include path and you are linking your executable against the library.

    #include <void_test.hpp>
    #include <vector>

    VOIDTEST_BEGIN

    void_test::unit("a test unit", [](){

        void_test::unit("a nested unit", [](){

            auto vector = std::vector<int>();
            void_test::assert_equal(vector.size(), 0u);
            void_test::assert_equal(vector.capacity(), 0u);

        });

        void_test::unit("some other unit", [](){

            auto vector = std::vector<int>(256);
            void_test::assert_equal(vector.size(), 256u);
            void_test::assert_equal(vector.capacity(), 256u);
            vector.push_back(0);
            void_test::assert_equal(vector.size(), 257u);
            void_test::assert_greater(vector.capacity(), 257u);

        });

    });

    VOIDTEST_END

# Notes

This library probably should not be used in its current state as it lacks a proper documentation and it may go through some API-breaking changes in the near future. Proceed with caution!
