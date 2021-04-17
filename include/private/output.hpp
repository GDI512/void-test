// ========================== output.hpp ==========================
//
//  Part of the citrine library, under the BSD-3-Clause License.
//  See https://github.com/GDI512/citrine/blob/master/LICENSE for
//  license information.
//
// ================================================================

#ifndef CITRINE_OUTPUT_HPP
#define CITRINE_OUTPUT_HPP

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
