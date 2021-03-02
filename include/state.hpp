#ifndef CPPLTF_STATE_HPP
#define CPPLTF_STATE_HPP

#include "utility.hpp"

namespace test::core {

    enum class exit_code : int { success = 0, failure = 1 };

    struct state {
        struct assert_struct {
            size_type total;
            size_type error;
        } assert;
        struct object_struct {
            size_type destroyed;
            size_type constructed;
        } object;
        struct error_struct {
            size_type destructor;
            size_type constructor;
            size_type assignment;
        } error;
    };

    class registry {
      private:
        static state global;

      private:
        state snapshot;

      public:
        ~registry() noexcept;
        registry() noexcept;
        registry(registry&& other) = delete;
        registry(const registry& other) = delete;

      public:
        auto operator=(registry&& other) -> registry& = delete;
        auto operator=(const registry& other) -> registry& = delete;

      public:
        auto empty() noexcept -> bool;
        auto status() noexcept -> bool;

      public:
        static auto on_error(string source) noexcept -> void;
        static auto on_success(string source) noexcept -> void;
        static auto on_exception(string source) noexcept -> void;
        static auto on_destruction() noexcept -> void;
        static auto on_construction() noexcept -> void;
        static auto on_destructor_error() noexcept -> void;
        static auto on_constructor_error() noexcept -> void;
        static auto on_operator_error() noexcept -> void;
    };

    extern exit_code code;

}

#endif
