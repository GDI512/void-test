#ifndef TEST_COMMON_HPP
#define TEST_COMMON_HPP

#include <assert.hpp>
#include <object.hpp>
#include <cstdlib>
#include <cstdio>

#define cassert(x)                                      \
    if (!(x)) {                                         \
        std::printf("Line: %i %s\n", __LINE__, #x);     \
        std::exit(1);                                   \
    }

#endif
