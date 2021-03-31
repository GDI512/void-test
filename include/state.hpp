#ifndef CPPLTF_STATE_HPP
#define CPPLTF_STATE_HPP

#include "utility.hpp"

namespace test {

    constexpr auto exit_failure = 1;
    constexpr auto exit_success = 0;

    struct state {
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
    };

    extern state global_state;
    extern integer exit_code;

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
        auto empty() const noexcept -> bool;
        auto status() const noexcept -> bool;
        auto result() const noexcept -> state;
    };

    auto is_ok(state::test data) noexcept -> bool;

    auto is_ok(state::resource data) noexcept -> bool;

    auto is_empty(state::test data) noexcept -> bool;

    auto is_empty(state::resource data) noexcept -> bool;

    template <message select>
    auto report() noexcept -> void = delete;

    template <message select>
    auto report(string source) noexcept -> bool = delete;

    template <>
    auto report<message::error>(string source) noexcept -> bool;

    template <>
    auto report<message::success>(string source) noexcept -> bool;

    template <>
    auto report<message::exception>() noexcept -> void;

    template <>
    auto report<message::destructor>() noexcept -> void;

    template <>
    auto report<message::constructor>() noexcept -> void;

    template <>
    auto report<message::destructor_error>() noexcept -> void;

    template <>
    auto report<message::constructor_error>() noexcept -> void;

    template <>
    auto report<message::operator_error>() noexcept -> void;

}

#endif
