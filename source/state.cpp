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

    state global = {};
    integer exit_code = exit_success;

    registry::~registry() noexcept {
        const auto result = difference();
        if (status() && !empty()) {
            print<message::unit_success>(result.check);
            print<message::unit_success>(result.object);
            restore();
        } else if (!status()) {
            exit_code = exit_failure;
            print<message::unit_error>(result.check);
            print<message::unit_error>(result.object);
            restore();
        }
    }

    registry::registry(string scope) noexcept {
        print<message::unit>(scope);
        save();
    }

    auto registry::save() noexcept -> void {
        snapshot = global;
        scope_level++;
    }

    auto registry::restore() noexcept -> void {
        global = snapshot;
        scope_level--;
    }

    auto registry::empty() const noexcept -> bool {
        const auto result = difference();
        return test::empty(result.check) && test::empty(result.object);
    }

    auto registry::status() const noexcept -> bool {
        const auto result = difference();
        return test::status(result.check) && test::status(result.object);
    }

    auto registry::difference() const noexcept -> state {
        return global - snapshot;
    }

    auto empty(state::test data) noexcept -> bool {
        return data.total_count + data.error_count == 0;
    }

    auto empty(state::resource data) noexcept -> bool {
        return data.destructor_count + data.constructor_count == 0 &&
            data.destructor_error_count + data.constructor_error_count + data.operator_error_count == 0;
    }

    auto status(state::test data) noexcept -> bool {
        return data.error_count == 0;
    }

    auto status(state::resource data) noexcept -> bool {
        return data.destructor_count == data.constructor_count &&
            data.destructor_error_count + data.constructor_error_count + data.operator_error_count == 0;
    }

    template <>
    auto report<message::error>() noexcept -> void {
        global.check.error_count++;
        global.check.total_count++;
    }

    template <>
    auto report<message::success>() noexcept -> void {
        global.check.total_count++;
    }

    template <>
    auto report<message::exception>() noexcept -> void {
        global.check.error_count++;
    }

    template <>
    auto report<message::destructor>() noexcept -> void {
        global.object.destructor_count++;
    }

    template <>
    auto report<message::constructor>() noexcept -> void {
        global.object.constructor_count++;
    }

    template <>
    auto report<message::destructor_error>() noexcept -> void {
        global.object.destructor_error_count++;
    }

    template <>
    auto report<message::constructor_error>() noexcept -> void {
        global.object.constructor_error_count++;
    }

    template <>
    auto report<message::operator_error>() noexcept -> void {
        global.object.operator_error_count++;
    }

}
