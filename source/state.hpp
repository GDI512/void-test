#ifndef CITRINE_STATE_HPP
#define CITRINE_STATE_HPP

#include "utility.hpp"

namespace test {

    extern int exit_code;

    enum class message {
        unit,
        exit,
        error,
        success,
        exception,
        destructor,
        constructor
    };

    extern struct state {
        int error_count;
        int total_count;
        int destroyed_count;
        int constructed_count;
    } current;

    class registry {
      private:
        state snapshot;

      public:
        ~registry() noexcept;
        registry(string scope) noexcept;
    };

    template <auto N>
    auto report() noexcept -> void = delete;

    template <auto N>
    auto report(state) noexcept -> void = delete;

    template <>
    auto report<message::error>() noexcept -> void;

    template <>
    auto report<message::success>() noexcept -> void;

    template <>
    auto report<message::exception>() noexcept -> void;

    template <>
    auto report<message::destructor>() noexcept -> void;

    template <>
    auto report<message::constructor>() noexcept -> void;

    template <>
    auto report<message::error>(state result) noexcept -> void;

    template <>
    auto report<message::success>(state result) noexcept -> void;

}

#endif
