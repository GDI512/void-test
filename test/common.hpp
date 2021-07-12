#ifndef CITRINE_TEST_COMMON_HPP
#define CITRINE_TEST_COMMON_HPP

#include <citrine.hpp>
#include <cstdlib>
#include <cstdio>

#define cassert(x)                                      \
    if (!(x)) {                                         \
        std::printf("Line: %i %s\n", __LINE__, #x);     \
        std::exit(1);                                   \
    }

#endif
