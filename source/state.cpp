// ========================== state.cpp ===========================
//
//  Part of the cppltf library, under the BSD-3-Clause License.
//  See https://github.com/GDI512/cppltf/blob/master/LICENSE for
//  license information.
//
// ================================================================

#include <utility.hpp>
#include <output.hpp>
#include <state.hpp>

namespace {

    using namespace test;

    auto operator-(state::test left, state::test right) noexcept {
        return state::test {
            left.error_count - right.error_count,
            left.total_count - right.total_count
        };
    }

    auto operator-(state::resource left, state::resource right) noexcept {
        return state::resource {
            left.destructor_count - right.destructor_count,
            left.constructor_count - right.constructor_count,
            left.destructor_error_count - right.destructor_error_count,
            left.constructor_error_count - right.constructor_error_count,
            left.operator_error_count - right.operator_error_count
        };
    }

    auto operator-(state left, state right) noexcept {
        return state {
            left.check - right.check,
            left.object - right.object
        };
    }

}

namespace test {

    state global_state = {};
    integer exit_code = exit_success;

    registry::~registry() noexcept {
        const auto difference = result();
        if (status() && !empty()) {
            display<message::unit_success>(difference.check);
            display<message::unit_success>(difference.object);
            restore();
        } else if (!status()) {
            exit_code = exit_failure;
            display<message::unit_error>(difference.check);
            display<message::unit_error>(difference.object);
            restore();
        }
    }

    registry::registry(string scope) noexcept {
        display<message::unit>(scope);
        save();
    }

    auto registry::save() noexcept -> void {
        snapshot = global_state;
        scope_level++;
    }

    auto registry::restore() noexcept -> void {
        global_state = snapshot;
        scope_level--;
    }

    auto registry::empty() const noexcept -> bool {
        const auto difference = result();
        return is_empty(difference.check) && is_empty(difference.object);
    }

    auto registry::status() const noexcept -> bool {
        const auto difference = result();
        return is_ok(difference.check) && is_ok(difference.object);
    }

    auto registry::result() const noexcept -> state {
        return global_state - snapshot;
    }

    auto is_ok(state::test data) noexcept -> bool {
        return data.error_count == 0;
    }

    auto is_ok(state::resource data) noexcept -> bool {
        return data.destructor_count == data.constructor_count &&
            data.destructor_error_count + data.constructor_error_count + data.operator_error_count == 0;
    }

    auto is_empty(state::test data) noexcept -> bool {
        return data.total_count + data.error_count == 0;
    }

    auto is_empty(state::resource data) noexcept -> bool {
        return data.destructor_count + data.constructor_count == 0 &&
            data.destructor_error_count + data.constructor_error_count + data.operator_error_count == 0;
    }

    template <>
    auto report<message::error>(string source) noexcept -> bool {
        global_state.check.error_count++;
        global_state.check.total_count++;
        display<message::error>(source);
        return false;
    }

    template <>
    auto report<message::success>(string source) noexcept -> bool {
        global_state.check.total_count++;
        display<message::success>(source);
        return true;
    }

    template <>
    auto report<message::exception>() noexcept -> void {
        global_state.check.error_count++;
        display<message::exception>();
    }

    template <>
    auto report<message::destructor>() noexcept -> void {
        global_state.object.destructor_count++;
    }

    template <>
    auto report<message::constructor>() noexcept -> void {
        global_state.object.constructor_count++;
    }

    template <>
    auto report<message::destructor_error>() noexcept -> void {
        global_state.object.destructor_error_count++;
    }

    template <>
    auto report<message::constructor_error>() noexcept -> void {
        global_state.object.constructor_error_count++;
    }

    template <>
    auto report<message::operator_error>() noexcept -> void {
        global_state.object.operator_error_count++;
    }

}
