#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdlib>
#include <cstring>

// clang-format off

#define CHECK(x) if (!(x)) { exit(1); }
#define CHECK_STREQUAL(x, y) if (!(strcmp(x, y) == 0)) { exit(1); }

// clang-format on

#endif
