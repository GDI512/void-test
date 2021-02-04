#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <void_test.hpp>
#include <forward_list>
#include <type_traits>
#include <utility>
#include <vector>
#include <limits>
#include <list>
#include <new>

auto stop(int code) noexcept -> void;

auto print(int line, const char* macro) noexcept -> void;

#define cassert(x)                                                                                                     \
    if (!(x)) {                                                                                                        \
        print(__LINE__, #x);                                                                                           \
        stop(1);                                                                                                       \
    }

#endif
