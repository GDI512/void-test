#ifndef CPPLTF_OUTPUT_HPP
#define CPPLTF_OUTPUT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test {

    extern integer scope_level;

    template <message select>
    auto print() noexcept -> void = delete;

    template <message select>
    auto print(string) noexcept -> void = delete;

    template <message select>
    auto print(state::test) noexcept -> void = delete;

    template <message select>
    auto print(state::resource) noexcept -> void = delete;

    template <>
    auto print<message::unit>(string name) noexcept -> void;

    template <>
    auto print<message::error>(string source) noexcept -> void;

    template <>
    auto print<message::success>(string source) noexcept -> void;

    template <>
    auto print<message::exception>() noexcept -> void;

    template <>
    auto print<message::unit_error>(state::test data) noexcept -> void;

    template <>
    auto print<message::unit_success>(state::test data) noexcept -> void;

    template <>
    auto print<message::unit_error>(state::resource data) noexcept -> void;

    template <>
    auto print<message::unit_success>(state::resource data) noexcept -> void;

}

#endif
