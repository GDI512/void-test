#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <void_test.hpp>

auto stop(int code) noexcept -> void;

auto print(int line, const char* macro) noexcept -> void;

#define cassert(x)                                                                                                     \
    if (!(x)) {                                                                                                        \
        print(__LINE__, #x);                                                                                           \
        stop(1);                                                                                                       \
    }

#endif
