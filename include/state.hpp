#ifndef VOID_TEST_STATE_HPP
#define VOID_TEST_STATE_HPP

#include "utility.hpp"

namespace void_test {

    constexpr auto exit_success = 0;
    constexpr auto exit_failure = 1;

    auto exit_status() noexcept -> int;

}

namespace void_test::core {

    extern int exit_code;

    template <typename T>
    class static_list {
      private:
        static static_list* active_node;

      private:
        static_list* previous_node;

      public:
        ~static_list() noexcept;
        static_list() noexcept;

      public:
        static auto current() noexcept -> T&;
    };

}

#endif
