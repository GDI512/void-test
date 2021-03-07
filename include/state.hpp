#ifndef CPPLTF_STATE_HPP
#define CPPLTF_STATE_HPP

#include "utility.hpp"

namespace test::core {

    enum class exit_code : int { success = 0, failure = 1 };

    struct state {
        size_type total_check_count;
        size_type check_error_count;
        size_type destroyed_count;
        size_type constructed_count;
        size_type destructor_error_count;
        size_type constructor_error_count;
        size_type assignment_error_count;
    };

    class registry {
      private:
        static state global;

      private:
        state snapshot;

      public:
        ~registry() noexcept;
        registry() noexcept;

      public:
        auto empty() noexcept -> bool;
        auto status() noexcept -> bool;

      public:
        static auto on_error() noexcept -> void;
        static auto on_success() noexcept -> void;
        static auto on_exception() noexcept -> void;
        static auto on_destruction() noexcept -> void;
        static auto on_construction() noexcept -> void;
        static auto on_destructor_error() noexcept -> void;
        static auto on_constructor_error() noexcept -> void;
        static auto on_operator_error() noexcept -> void;
    };

    auto operator-(state left, state right) noexcept -> state;
    auto operator-=(state& left, state right) noexcept -> state&;

    extern exit_code code;

}

#endif
