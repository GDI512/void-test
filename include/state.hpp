#ifndef VOID_TEST_STATE_HPP
#define VOID_TEST_STATE_HPP

#include "utility.hpp"

namespace test::core {

    constexpr int exit_success = 0;
    constexpr int exit_failure = 1;

    struct info_struct {
        int exit_code;
    };

    struct test_struct {
        size_t total_count;
        size_t error_count;
    };

    struct object_struct {
        size_t destroyed_count;
        size_t constructed_count;
        size_t destructor_error_count;
        size_t constructor_error_count;
        size_t operator_error_count;
    };

    extern struct global_struct {
        info_struct info;
        test_struct test;
        object_struct object;
    } global;

    class registry {
      private:
        test_struct snapshot;

      public:
        ~registry() noexcept;
        registry() noexcept;
        registry(registry&& other) = delete;
        registry(const registry& other) = delete;

      public:
        auto operator=(registry&& other) -> registry& = delete;
        auto operator=(const registry& other) -> registry& = delete;

      public:
        static auto on_error(const char* source) noexcept -> bool;
        static auto on_success(const char* source) noexcept -> bool;
        static auto on_exception(const char* source) noexcept -> void;
    };

    class verifier {
      private:
        object_struct snapshot;

      public:
        ~verifier() noexcept;
        verifier() noexcept;
        verifier(verifier&& other) = delete;
        verifier(const verifier& other) = delete;

      public:
        auto operator=(verifier&& other) -> verifier& = delete;
        auto operator=(const verifier& other) -> verifier& = delete;

      public:
        static auto on_destruction() noexcept -> void;
        static auto on_construction() noexcept -> void;
        static auto on_destructor_error() noexcept -> void;
        static auto on_constructor_error() noexcept -> void;
        static auto on_operator_error() noexcept -> void;
    };

    auto is_ok(test_struct state) noexcept -> bool;
    auto is_ok(object_struct state) noexcept -> bool;

    auto is_empty(test_struct state) noexcept -> bool;
    auto is_empty(object_struct state) noexcept -> bool;

    auto exit_code() noexcept -> int;
    auto exit_code(int code) noexcept -> void;

    auto operator+(test_struct left, test_struct right) noexcept -> test_struct;
    auto operator-(test_struct left, test_struct right) noexcept -> test_struct;

    auto operator+=(test_struct& left, test_struct right) noexcept -> test_struct&;
    auto operator-=(test_struct& left, test_struct right) noexcept -> test_struct&;

    auto operator+(object_struct left, object_struct right) noexcept -> object_struct;
    auto operator-(object_struct left, object_struct right) noexcept -> object_struct;

    auto operator+=(object_struct& left, object_struct right) noexcept -> object_struct&;
    auto operator-=(object_struct& left, object_struct right) noexcept -> object_struct&;

}

#endif
