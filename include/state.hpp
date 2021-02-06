#ifndef VOID_TEST_STATE_HPP
#define VOID_TEST_STATE_HPP

#include "utility.hpp"

namespace test::core {

    enum class exit_code : int { success = 0, failure = 1, internal_error = 2 };

    struct test_struct {
        size_t total_count;
        size_t error_count;
        auto is_ok() const noexcept -> bool;
        auto is_empty() const noexcept -> bool;
    };

    struct object_struct {
        size_t destroyed_count;
        size_t constructed_count;
        size_t destructor_error_count;
        size_t constructor_error_count;
        size_t operator_error_count;
        auto is_ok() const noexcept -> bool;
        auto is_empty() const noexcept -> bool;
    };

    struct global_struct {
        test_struct test_state;
        object_struct object_state;
    };

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

    auto operator+(test_struct left, test_struct right) noexcept -> test_struct;
    auto operator-(test_struct left, test_struct right) noexcept -> test_struct;

    auto operator+=(test_struct& left, test_struct right) noexcept -> test_struct&;
    auto operator-=(test_struct& left, test_struct right) noexcept -> test_struct&;

    auto operator+(object_struct left, object_struct right) noexcept -> object_struct;
    auto operator-(object_struct left, object_struct right) noexcept -> object_struct;

    auto operator+=(object_struct& left, object_struct right) noexcept -> object_struct&;
    auto operator-=(object_struct& left, object_struct right) noexcept -> object_struct&;

    extern exit_code code;
    extern global_struct global;

}

#endif
