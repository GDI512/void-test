# About
The *void_test* testing framework is designed to have minimal impact on compile times.
It does not rely on macros and is very easy to integrate into other CMake projects.

# Features
* **Macro-free** - There are no assertion or test case macros, instead, this framework makes extensive use of C++11 lambdas and templates to achieve similar functionality.
* **Fast to compile** - The header files do not include any system headers or other external dependencies to minimize impact on compile times. All code which can and should be precompiled is compiled into a static library.
* **Easy to use** - Everything from building to writing tests is as straightforward as possible.

# Getting started
For tutorial and basic API documentation, see [wiki](https://github.com/GDI512/void-test/wiki).
