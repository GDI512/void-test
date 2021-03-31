#ifndef CPPLTF_OUTPUT_HPP
#define CPPLTF_OUTPUT_HPP

#include "state.hpp"
#include "utility.hpp"

namespace test {

    extern integer scope_level;

    template <message select>
    auto display() noexcept -> void = delete;

    template <message select>
    auto display(string) noexcept -> void = delete;

    template <message select>
    auto display(state::test) noexcept -> void = delete;

    template <message select>
    auto display(state::resource) noexcept -> void = delete;

    template <>
    auto display<message::unit>(string name) noexcept -> void;

    template <>
    auto display<message::error>(string source) noexcept -> void;

    template <>
    auto display<message::success>(string source) noexcept -> void;

    template <>
    auto display<message::exception>() noexcept -> void;

    template <>
    auto display<message::unit_error>(state::test data) noexcept -> void;

    template <>
    auto display<message::unit_success>(state::test data) noexcept -> void;

    template <>
    auto display<message::unit_error>(state::resource data) noexcept -> void;

    template <>
    auto display<message::unit_success>(state::resource data) noexcept -> void;

}

#endif
