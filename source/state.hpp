#ifndef CITRINE_STATE_HPP
#define CITRINE_STATE_HPP

#include "utility.hpp"

namespace citrine {

    extern int exit_code;
    extern int indent_count;

    class unit_state {
      public:
        struct state {
            size_type error_count;
            size_type check_count;
            size_type destroyed_count;
            size_type constructed_count;
        };

      private:
        static unit_state* current;

      private:
        unit_state* previous;
        state snapshot;

      public:
        ~unit_state() noexcept;
        unit_state(string scope = "") noexcept;

      public:
        static auto active() noexcept -> unit_state&;

      public:
        auto on_error(string check = "") noexcept -> bool;
        auto on_success(string check = "") noexcept -> bool;
        auto on_exception() noexcept -> void;
        auto on_destruction() noexcept -> void;
        auto on_construction() noexcept -> void;

      public:
        auto get() const noexcept -> state;
        auto good() const noexcept -> bool;
        auto empty() const noexcept -> bool;
    };

    auto print(string format, ...) noexcept -> void;

    auto print_unit(string name) noexcept -> void;

    auto print_error(string check) noexcept -> void;

    auto print_success(string check) noexcept -> void;

    auto print_exception() noexcept -> void;

    auto print_unit_error(unit_state::state data) noexcept -> void;

    auto print_unit_success(unit_state::state data) noexcept -> void;

}

#endif
