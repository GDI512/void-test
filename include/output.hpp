#ifndef VOID_TEST_OUTPUT_HPP
#define VOID_TEST_OUTPUT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test::core {

    extern uint indent_level;

    class scope {
      public:
        ~scope() noexcept;
        scope(string name) noexcept;
        scope(scope&& other) = delete;
        scope(const scope& other) = delete;

      public:
        auto operator=(scope&& other) -> scope& = delete;
        auto operator=(const scope& other) -> scope& = delete;
    };

    auto print_error(string source) noexcept -> void;

    auto print_success(string source) noexcept -> void;

    auto print_exception(string source) noexcept -> void;

    auto print_registry_error(test_struct state) noexcept -> void;

    auto print_registry_success(test_struct state) noexcept -> void;

    auto print_verifier_error(object_struct state) noexcept -> void;

    auto print_verifier_success(object_struct state) noexcept -> void;

}

#endif
