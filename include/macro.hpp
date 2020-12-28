#ifndef VOID_TEST_MACRO_HPP
#define VOID_TEST_MACRO_HPP

#include "state.hpp"

// clang-format off

#define VOID_TEST_BEGIN int main() {
#define VOID_TEST_END return test::exit_status(); }

// clang-format on

#endif
