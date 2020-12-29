#ifndef VOID_TEST_STATE_HPP
#define VOID_TEST_STATE_HPP

#include "utility.hpp"

namespace void_test {

    constexpr auto exit_success = 0;
    constexpr auto exit_failure = 1;

    auto exit_status() noexcept -> int;

}

namespace void_test::core {

    extern int exit_status;

}

#endif
