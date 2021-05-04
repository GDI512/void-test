// ========================== state.cpp ===========================
//
//  Part of the citrine library, under the BSD-3-Clause License.
//  See https://github.com/GDI512/citrine/blob/master/LICENSE for
//  license information.
//
// ================================================================

#include "output.hpp"
#include "state.hpp"

namespace {

    using namespace test;

    auto operator-(state left, state right) noexcept {
        return state {
            left.error_count - right.error_count,
            left.total_count - right.total_count,
            left.destroyed_count - right.destroyed_count,
            left.constructed_count - right.constructed_count,
        };
    }

    auto operator-=(state& left, state right) noexcept {
        left.error_count -= right.error_count;
        left.total_count -= right.total_count;
        left.destroyed_count -= right.destroyed_count;
        left.constructed_count -= right.constructed_count;
    }

}

namespace test {

    int exit_code = {};
    state current = {};

    registry::~registry() noexcept {
        const auto result = current - snapshot;
        if (result.error_count > 0 || result.destroyed_count != result.constructed_count) {
            print<message::error>(result);
            report<message::error>(result);
        } else if (result.total_count + result.destroyed_count > 0) {
            print<message::success>(result);
            report<message::success>(result);
        }
    }

    registry::registry(string scope) noexcept : snapshot(current) {
        print<message::unit>(scope);
    }

    template <>
    auto report<message::error>() noexcept -> void {
        current.error_count++;
        current.total_count++;
    }

    template <>
    auto report<message::success>() noexcept -> void {
        current.total_count++;
    }

    template <>
    auto report<message::exception>() noexcept -> void {
        current.error_count++;
    }

    template <>
    auto report<message::destructor>() noexcept -> void {
        current.destroyed_count++;
    }

    template <>
    auto report<message::constructor>() noexcept -> void {
        current.constructed_count++;
    }

    template <>
    auto report<message::error>(state result) noexcept -> void {
        exit_code = 1;
        current -= result;
        indent--;
    }

    template <>
    auto report<message::success>(state result) noexcept -> void {
        current -= result;
        indent--;
    }

}
