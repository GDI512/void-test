#ifndef CPPLTF_STATE_HPP
#define CPPLTF_STATE_HPP

#include "utility.hpp"

namespace test {

    extern int scope_nesting;

    constexpr auto exit_failure = 1;
    constexpr auto exit_success = 0;

    struct state {
        struct test {
            int error_count = 0;
            int total_count = 0;
        } check;
        struct resource {
            int destructor_count = 0;
            int constructor_count = 0;
            int destructor_error_count = 0;
            int constructor_error_count = 0;
            int operator_error_count = 0;
        } object;
    };

    class registry {
      public:
        static int exit;
        static state global;

      private:
        state snapshot;

      public:
        ~registry() noexcept;
        registry(string scope) noexcept;
        registry(registry&& other) = delete;
        registry(const registry& other) = delete;

      public:
        auto operator=(registry&& other) -> registry& = delete;
        auto operator=(const registry& other) -> registry& = delete;

      public:
        auto good() const noexcept -> bool;
        auto empty() const noexcept -> bool;
        auto result() const noexcept -> state;
        auto save() noexcept -> void;
        auto restore() noexcept -> void;
    };

    auto print_unit(string name) noexcept -> void;

    auto print_error(string source) noexcept -> void;

    auto print_success(string source) noexcept -> void;

    auto print_exception(string source) noexcept -> void;

    auto print_unit_error(state::test data) noexcept -> void;

    auto print_unit_success(state::test data) noexcept -> void;

    auto print_unit_error(state::resource data) noexcept -> void;

    auto print_unit_success(state::resource data) noexcept -> void;

    auto report_error() noexcept -> void;

    auto report_success() noexcept -> void;

    auto report_exception() noexcept -> void;

    auto report_destruction() noexcept -> void;

    auto report_construction() noexcept -> void;

    auto report_destructor_error() noexcept -> void;

    auto report_constructor_error() noexcept -> void;

    auto report_operator_error() noexcept -> void;

    auto on_exit() noexcept -> int;

    auto on_error(string source) noexcept -> bool;

    auto on_success(string source) noexcept -> bool;

    auto on_exception(string source) noexcept -> void;

    auto on_destruction() noexcept -> void;

    auto on_construction() noexcept -> void;

    auto on_destructor_error() noexcept -> void;

    auto on_constructor_error() noexcept -> void;

    auto on_operator_error() noexcept -> void;

}

#endif
