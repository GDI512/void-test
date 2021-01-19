#include "common.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

auto stop(int code) noexcept -> void {
    exit(code);
}

auto print(int line, const char* macro) noexcept -> void {
    printf("Line: %i %s\n", __LINE__, macro);
}

auto cmpstr(const char* string, const char* other) noexcept -> int {
    return strcmp(string, other);
}
