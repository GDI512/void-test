#include "common.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

auto stop(int code) noexcept -> void {
    exit(code);
}

auto print(int line, const char* macro) noexcept -> void {
    printf("Line: %i %s\n", line, macro);
}
