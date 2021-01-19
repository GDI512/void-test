#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <void_test.hpp>

auto stop(int code) noexcept -> void;

auto print(int line, const char* macro) noexcept -> void;

auto cmpstr(const char* string, const char* other) noexcept -> int;

#endif
