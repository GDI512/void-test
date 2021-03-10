#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <cppltf.hpp>
#include <cstdlib>
#include <cstring>
#include <cstdio>

inline auto stop(int code) noexcept {
    std::exit(code);
}

inline auto print(int line, const char* macro) noexcept {
    std::printf("Line: %i %s\n", line, macro);
}

#define cassert(x)             \
    if (!(x)) {                \
        print(__LINE__, #x);   \
        stop(1);               \
    }

#endif
