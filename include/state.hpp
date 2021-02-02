#ifndef VOIDTEST_STATE_HPP
#define VOIDTEST_STATE_HPP

#include "utility.hpp"

namespace test::core {

    struct info_struct {
        int exit_code;
    };

    struct test_struct {
        uint total_count;
        uint error_count;
    };

    struct object_struct {
        uint destroyed_count;
        uint constructed_count;
        uint destructor_error_count;
        uint constructor_error_count;
        uint operator_error_count;
    };

    extern struct global_struct {
        info_struct info;
        test_struct test;
        object_struct object;
    } global;

    constexpr int exit_success = 0;
    constexpr int exit_failure = 1;

    class registry {
      private:
        test_struct snapshot;
        global_struct& state;

      public:
        ~registry() noexcept;
        registry(global_struct& state = global) noexcept;
        registry(registry&& other) = delete;
        registry(const registry& other) = delete;

      public:
        auto operator=(registry&& other) -> registry& = delete;
        auto operator=(const registry& other) -> registry& = delete;
    };

    class verifier {
      private:
        object_struct snapshot;
        global_struct& state;

      public:
        ~verifier() noexcept;
        verifier(global_struct& state = global) noexcept;
        verifier(verifier&& other) = delete;
        verifier(const verifier& other) = delete;

      public:
        auto operator=(verifier&& other) -> verifier& = delete;
        auto operator=(const verifier& other) -> verifier& = delete;
    };

    auto is_ok(test_struct state) noexcept -> bool;
    auto is_ok(object_struct state) noexcept -> bool;

    auto is_empty(test_struct state) noexcept -> bool;
    auto is_empty(object_struct state) noexcept -> bool;

    auto exit_code(const global_struct& data = global) noexcept -> int;
    auto exit_code(int code, global_struct& data = global) noexcept -> void;

    auto register_error(global_struct& data = global) noexcept -> void;
    auto register_success(global_struct& data = global) noexcept -> void;
    auto register_exception(global_struct& data = global) noexcept -> void;
    auto register_destruction(global_struct& data = global) noexcept -> void;
    auto register_construction(global_struct& data = global) noexcept -> void;
    auto register_destructor_error(global_struct& data = global) noexcept -> void;
    auto register_constructor_error(global_struct& data = global) noexcept -> void;
    auto register_operator_error(global_struct& data = global) noexcept -> void;

    auto on_error(string source, global_struct& data = global) noexcept -> bool;
    auto on_success(string source, global_struct& data = global) noexcept -> bool;
    auto on_exception(string source, global_struct& data = global) noexcept -> bool;
    auto on_destruction(global_struct& data = global) noexcept -> void;
    auto on_construction(global_struct& data = global) noexcept -> void;
    auto on_destructor_error(global_struct& data = global) noexcept -> void;
    auto on_constructor_error(global_struct& data = global) noexcept -> void;
    auto on_operator_error(global_struct& data = global) noexcept -> void;

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
