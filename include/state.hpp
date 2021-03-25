#ifndef CPPLTF_STATE_HPP
#define CPPLTF_STATE_HPP

#include "utility.hpp"

namespace test {

    constexpr auto exit_failure = 1;
    constexpr auto exit_success = 0;

    extern integer exit_code;

    extern integer scope_level;

    extern struct state {
        struct test {
            integer error_count;
            integer total_count;
        } check;
        struct resource {
            integer destructor_count;
            integer constructor_count;
            integer destructor_error_count;
            integer constructor_error_count;
            integer operator_error_count;
        } object;
    } global;

    class registry {
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
        auto save() noexcept -> void;
        auto restore() noexcept -> void;
        auto ok() const noexcept -> bool;
        auto empty() const noexcept -> bool;
        auto difference() const noexcept -> state;
    };

    auto on_error(string source) noexcept -> bool;

    auto on_success(string source) noexcept -> bool;

    auto on_exception() noexcept -> void;

    auto on_destructor() noexcept -> void;

    auto on_constructor() noexcept -> void;

    auto on_destructor_error() noexcept -> void;

    auto on_constructor_error() noexcept -> void;

    auto on_operator_error() noexcept -> void;

}

#endif
