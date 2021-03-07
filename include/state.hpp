#ifndef CPPLTF_STATE_HPP
#define CPPLTF_STATE_HPP

#include "utility.hpp"

namespace test::core {

    using state_array = array<size_type, 7>;

    enum exit_code { success, failure };

    enum state { checks, errors, destructors, constructors, destructor_errors, constructor_errors, assignment_errors };

    class registry {
      private:
        static exit_code code;
        static state_array global;

      private:
        state_array snapshot;

      public:
        ~registry() noexcept;
        registry() noexcept;

      public:
        auto data() noexcept -> state_array;
        auto empty() noexcept -> bool;
        auto status() noexcept -> bool;

      public:
        static auto on_exit() noexcept -> int;
        static auto on_error() noexcept -> void;
        static auto on_success() noexcept -> void;
        static auto on_exception() noexcept -> void;
        static auto on_destruction() noexcept -> void;
        static auto on_construction() noexcept -> void;
        static auto on_destructor_error() noexcept -> void;
        static auto on_constructor_error() noexcept -> void;
        static auto on_operator_error() noexcept -> void;
    };

}

#endif
