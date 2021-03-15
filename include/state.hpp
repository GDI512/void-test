#ifndef CPPLTF_STATE_HPP
#define CPPLTF_STATE_HPP

#include "utility.hpp"

namespace test {

    constexpr auto exit_failure = 1;
    constexpr auto exit_success = 0;

    class state;

    class output {
      private:
        static int level;

      public:
        ~output() noexcept;
        output(string name) noexcept;
        output(output&& other) = delete;
        output(const output& other) = delete;

      public:
        auto operator=(output&& other) -> output& = delete;
        auto operator=(const output& other) -> output& = delete;

      public:
        static auto on_error(string source) noexcept -> void;
        static auto on_success(string source) noexcept -> void;
        static auto on_exception() noexcept -> void;
        static auto on_rollback(state snapshot, bool is_ok) noexcept -> void;
    };

    class state {
      friend class output;

      private:
        static int code;
        static state global;

      private:
        int error_count = 0;
        int check_count = 0;
        int destroyed_count = 0;
        int constructed_count = 0;
        int destructor_error_count = 0;
        int constructor_error_count = 0;
        int operator_error_count = 0;

      public:
        auto operator-(state other) noexcept -> state;
        auto operator-=(state other) noexcept -> state&;

      public:
        auto is_ok() noexcept -> bool;
        auto is_empty() noexcept -> bool;

      public:
        static auto get() noexcept -> state;
        static auto on_exit() noexcept -> int;
        static auto on_exit(int value) noexcept -> void;
        static auto on_error() noexcept -> void;
        static auto on_success() noexcept -> void;
        static auto on_exception() noexcept -> void;
        static auto on_destruction() noexcept -> void;
        static auto on_construction() noexcept -> void;
        static auto on_destructor_error() noexcept -> void;
        static auto on_constructor_error() noexcept -> void;
        static auto on_operator_error() noexcept -> void;
        static auto on_rollback(state snapshot) noexcept -> void;
    };

    class registry {
      private:
        state snapshot;
        output printer;

      public:
        ~registry() noexcept;
        registry(string scope) noexcept;
        registry(registry&& other) = delete;
        registry(const registry& other) = delete;

      public:
        auto operator=(registry&& other) -> registry& = delete;
        auto operator=(const registry& other) -> registry& = delete;

      public:
        auto is_ok() noexcept -> bool;
        auto is_empty() noexcept -> bool;

      public:
        static auto on_exit() noexcept -> int;
        static auto on_error(string source) noexcept -> bool;
        static auto on_success(string source) noexcept -> bool;
        static auto on_exception() noexcept -> void;
        static auto on_destruction() noexcept -> void;
        static auto on_construction() noexcept -> void;
        static auto on_destructor_error() noexcept -> void;
        static auto on_constructor_error() noexcept -> void;
        static auto on_operator_error() noexcept -> void;
    };

}

#endif
