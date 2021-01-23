#ifndef VOID_TEST_STATE_HPP
#define VOID_TEST_STATE_HPP

#include "utility.hpp"

namespace test::core {

    constexpr int exit_success = 0;
    constexpr int exit_failure = 1;

    struct test_state {
        size_type total_count;
        size_type error_count;
    };

    struct resource_state {
        size_type destroyed_count;
        size_type constructed_count;
        size_type destructor_error_count;
        size_type constructor_error_count;
        size_type operator_error_count;
    };

    extern int global_exit_code;
    extern test_state global_test_state;
    extern resource_state global_resource_state;

    class registry {
      private:
        test_state snapshot;

      public:
        ~registry() noexcept;
        registry() noexcept;
        registry(registry&& other) = delete;
        registry(const registry& other) = delete;

      public:
        auto operator=(registry&& other) -> registry& = delete;
        auto operator=(const registry& other) -> registry& = delete;
    };

    class verifier {
      private:
        resource_state snapshot;

      public:
        ~verifier() noexcept;
        verifier() noexcept;
        verifier(verifier&& other) = delete;
        verifier(const verifier& other) = delete;

      public:
        auto operator=(verifier&& other) -> verifier& = delete;
        auto operator=(const verifier& other) -> verifier& = delete;
    };

    auto exit_code() noexcept -> int;

    auto on_error(string source) noexcept -> bool;

    auto on_success(string source) noexcept -> bool;

    auto on_exception(string source) noexcept -> bool;

    auto on_destruction() noexcept -> void;

    auto on_construction() noexcept -> void;

    auto on_destructor_error() noexcept -> void;

    auto on_constructor_error() noexcept -> void;

    auto on_operator_error() noexcept -> void;

    auto operator+(test_state left, test_state right) noexcept -> test_state;

    auto operator-(test_state left, test_state right) noexcept -> test_state;

    auto operator+=(test_state& left, test_state right) noexcept -> test_state&;

    auto operator-=(test_state& left, test_state right) noexcept -> test_state&;

    auto operator+(resource_state left, resource_state right) noexcept -> resource_state;

    auto operator-(resource_state left, resource_state right) noexcept -> resource_state;

    auto operator+=(resource_state& left, resource_state right) noexcept -> resource_state&;

    auto operator-=(resource_state& left, resource_state right) noexcept -> resource_state&;

}

#endif
