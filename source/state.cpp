#include <output.hpp>
#include <state.hpp>

namespace {

    using namespace test;

    auto empty(core::state state) noexcept {
        return state.assert.total + state.object.constructed + state.object.destroyed == 0;
    }

    auto status(core::state::assert_struct state) noexcept {
        return state.error == 0;
    }

    auto status(core::state::object_struct state) noexcept {
        return state.destroyed == state.constructed;
    }

    auto status(core::state::error_struct state) noexcept {
        return state.destructor + state.constructor + state.assignment == 0;
    }

    auto status(core::state state) noexcept {
        const auto assert_status = ::status(state.assert);
        const auto object_status = ::status(state.object);
        const auto error_status = ::status(state.error);
        return assert_status && object_status && error_status;
    }

    auto difference(core::state::assert_struct state, core::state::assert_struct snapshot) noexcept {
        auto result = decltype(state){};
        result.total = state.total - snapshot.total;
        result.error = state.error - snapshot.error;
        return result;
    }

    auto difference(core::state::object_struct state, core::state::object_struct snapshot) noexcept {
        auto result = decltype(state){};
        result.destroyed = state.destroyed - snapshot.destroyed;
        result.constructed = state.constructed - snapshot.constructed;
        return result;
    }

    auto difference(core::state::error_struct state, core::state::error_struct snapshot) noexcept {
        auto result = decltype(state){};
        result.destructor = state.destructor - snapshot.destructor;
        result.constructor = state.constructor - snapshot.constructor;
        result.assignment = state.assignment - snapshot.assignment;
        return result;
    }

    auto difference(core::state state, core::state snapshot) noexcept {
        auto result = core::state{};
        result.assert = ::difference(state.assert, snapshot.assert);
        result.object = ::difference(state.object, snapshot.object);
        result.error = ::difference(state.error, snapshot.error);
        return result;
    }

    auto rollback(core::state::assert_struct& state, core::state::assert_struct snapshot) noexcept {
        state.total -= snapshot.total;
        state.error -= snapshot.error;
    }

    auto rollback(core::state::object_struct& state, core::state::object_struct snapshot) noexcept {
        state.destroyed -= snapshot.destroyed;
        state.constructed -= snapshot.constructed;
    }

    auto rollback(core::state::error_struct& state, core::state::error_struct snapshot) noexcept {
        state.destructor -= snapshot.destructor;
        state.constructor -= snapshot.constructor;
        state.assignment -= snapshot.assignment;
    }

    auto rollback(core::state& state, core::state snapshot) noexcept {
        ::rollback(state.assert, snapshot.assert);
        ::rollback(state.object, snapshot.object);
        ::rollback(state.error, snapshot.error);
    }

    auto on_exit(core::exit_code value) noexcept {
        core::code = value;
    }

    auto on_error(core::state::assert_struct& state) noexcept {
        ++state.total;
        ++state.error;
    }

    auto on_success(core::state::assert_struct& state) noexcept {
        ++state.total;
    }

    auto on_destruction(core::state::object_struct& state) noexcept {
        ++state.destroyed;
    }

    auto on_construction(core::state::object_struct& state) noexcept {
        ++state.constructed;
    }

    auto on_destructor_error(core::state::error_struct& state) noexcept {
        ++state.destructor;
    }

    auto on_constructor_error(core::state::error_struct& state) noexcept {
        ++state.constructor;
    }

    auto on_operator_error(core::state::error_struct& state) noexcept {
        ++state.assignment;
    }

}

namespace test::core {

    exit_code code = exit_code::success;

    state registry::global = {};

    registry::~registry() noexcept {
        const auto result = ::difference(global, snapshot);
        if (!empty() && status()) {
            output::on_unit_success(result);
            ::rollback(global, result);
        } else {
            output::on_unit_error(result);
            ::rollback(global, result);
            ::on_exit(exit_code::failure);
        }
    }

    registry::registry() noexcept : snapshot(global) {}

    auto registry::empty() noexcept -> bool {
        const auto result = ::difference(global, snapshot);
        return ::empty(result);
    }

    auto registry::status() noexcept -> bool {
        const auto result = ::difference(global, snapshot);
        return ::status(result);
    }

    auto registry::on_error(string source) noexcept -> void {
        output::on_error(source);
        ::on_error(global.assert);
    }

    auto registry::on_success(string source) noexcept -> void {
        output::on_success(source);
        ::on_success(global.assert);
    }

    auto registry::on_exception(string source) noexcept -> void {
        output::on_exception(source);
        ::on_error(global.assert);
    }

    auto registry::on_destruction() noexcept -> void {
        ::on_destruction(global.object);
    }

    auto registry::on_construction() noexcept -> void {
        ::on_construction(global.object);
    }

    auto registry::on_destructor_error() noexcept -> void {
        ::on_destructor_error(global.error);
    }

    auto registry::on_constructor_error() noexcept -> void {
        ::on_constructor_error(global.error);
    }

    auto registry::on_operator_error() noexcept -> void {
        ::on_operator_error(global.error);
    }

}
