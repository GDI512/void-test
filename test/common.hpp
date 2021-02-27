#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <cppltf.hpp>
#include <cstdlib>
#include <cstdio>

inline auto stop(int code) noexcept {
    exit(code);
}

inline auto print(int line, const char* macro) noexcept {
    printf("Line: %i %s\n", line, macro);
}

#define cassert(x)             \
    if (!(x)) {                \
        print(__LINE__, #x);   \
        stop(1);               \
    }

#endif
