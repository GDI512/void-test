// ========================== output.hpp ==========================
//
//  Part of the citrine library, under the BSD-3-Clause License.
//  See https://github.com/GDI512/citrine/blob/master/LICENSE for
//  license information.
//
// ================================================================

#ifndef CITRINE_OUTPUT_HPP
#define CITRINE_OUTPUT_HPP

#include "utility.hpp"
#include "state.hpp"

namespace test {

    extern int indent;

    template <auto N>
    auto print(state) noexcept -> void = delete;

    template <auto N>
    auto print(string) noexcept -> void = delete;

    template <>
    auto print<message::unit>(string name) noexcept -> void;

    template <>
    auto print<message::error>(string source) noexcept -> void;

    template <>
    auto print<message::success>(string source) noexcept -> void;

    template <>
    auto print<message::exception>(string source) noexcept -> void;

    template <>
    auto print<message::error>(state data) noexcept -> void;

    template <>
    auto print<message::success>(state data) noexcept -> void;

}

#endif
