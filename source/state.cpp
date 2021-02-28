#include <output.hpp>
#include <state.hpp>

namespace {

    using namespace test;

    struct assert_tag {};
    struct object_tag {};
    struct error_tag {};

    constexpr auto code(aux::exit_code value) noexcept {
        aux::exit_value = value;
    }

    constexpr auto empty(aux::state state) noexcept {
        return state.assert.total + state.object.constructed + state.object.destroyed == 0;
    }

    constexpr auto on_error(aux::state& state) noexcept {
        ++state.assert.total;
        ++state.assert.error;
    }

    constexpr auto on_success(aux::state& state) noexcept {
        ++state.assert.total;
    }

    constexpr auto on_destruction(aux::state& state) noexcept {
        ++state.object.destroyed;
    }

    constexpr auto on_construction(aux::state& state) noexcept {
        ++state.object.constructed;
    }

    constexpr auto on_destructor_error(aux::state& state) noexcept {
        ++state.error.destructor;
    }

    constexpr auto on_constructor_error(aux::state& state) noexcept {
        ++state.error.constructor;
    }

    constexpr auto on_operator_error(aux::state& state) noexcept {
        ++state.error.assignment;
    }

    constexpr auto difference(aux::state state, aux::state snapshot, assert_tag) noexcept {
        auto result = decltype(snapshot.assert){};
        result.total = state.assert.total - snapshot.assert.total;
        result.error = state.assert.error - snapshot.assert.error;
        return result;
    }

    constexpr auto difference(aux::state state, aux::state snapshot, object_tag) noexcept {
        auto result = decltype(snapshot.object){};
        result.destroyed = state.object.destroyed - snapshot.object.destroyed;
        result.constructed = state.object.constructed - snapshot.object.constructed;
        return result;
    }

    constexpr auto difference(aux::state state, aux::state snapshot, error_tag) noexcept {
        auto result = decltype(snapshot.error){};
        result.destructor = state.error.destructor - snapshot.error.destructor;
        result.constructor = state.error.constructor - snapshot.error.constructor;
        result.assignment = state.error.assignment - snapshot.error.assignment;
        return result;
    }

    constexpr auto difference(aux::state state, aux::state snapshot) noexcept {
        auto result = aux::state{};
        result.assert = ::difference(state, snapshot, assert_tag{});
        result.object = ::difference(state, snapshot, object_tag{});
        result.error = ::difference(state, snapshot, error_tag{});
        return result;
    }

    constexpr auto restore(aux::state& state, aux::state snapshot, assert_tag) noexcept {
        state.assert.total -= snapshot.assert.total;
        state.assert.error -= snapshot.assert.error;
    }

    constexpr auto restore(aux::state& state, aux::state snapshot, object_tag) noexcept {
        state.object.destroyed -= snapshot.object.destroyed;
        state.object.constructed -= snapshot.object.constructed;
    }

    constexpr auto restore(aux::state& state, aux::state snapshot, error_tag) noexcept {
        state.error.destructor -= snapshot.error.destructor;
        state.error.constructor -= snapshot.error.constructor;
        state.error.assignment -= snapshot.error.assignment;
    }

    constexpr auto restore(aux::state& state, aux::state snapshot) noexcept {
        ::restore(state, snapshot, assert_tag{});
        ::restore(state, snapshot, object_tag{});
        ::restore(state, snapshot, error_tag{});
    }

    constexpr auto status(aux::state state, assert_tag) noexcept {
        return state.assert.error == 0;
    }

    constexpr auto status(aux::state state, object_tag) noexcept {
        return state.object.destroyed == state.object.constructed;
    }

    constexpr auto status(aux::state state, error_tag) noexcept {
        return state.error.destructor + state.error.constructor + state.error.assignment == 0;
    }

    constexpr auto status(aux::state state) noexcept {
        const auto assert_status = ::status(state, assert_tag{});
        const auto object_status = ::status(state, object_tag{});
        const auto error_status = ::status(state, error_tag{});
        return assert_status && object_status && error_status;
    }

}

namespace test::aux {

    exit_code exit_value = exit_code::success;

    state registry::global = {};

    registry::~registry() noexcept {
        const auto result = ::difference(global, snapshot);
        if (!empty() && status()) {
            output::on_unit_success(result);
            ::restore(global, result);
        } else {
            output::on_unit_error(result);
            ::restore(global, result);
            ::code(exit_code::failure);
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

    auto registry::on_error(const char* source) noexcept -> void {
        output::on_error(source);
        ::on_error(global);
    }

    auto registry::on_success(const char* source) noexcept -> void {
        output::on_success(source);
        ::on_success(global);
    }

    auto registry::on_exception(const char* source) noexcept -> void {
        output::on_exception(source);
        ::on_error(global);
    }

    auto registry::on_destruction() noexcept -> void {
        ::on_destruction(global);
    }

    auto registry::on_construction() noexcept -> void {
        ::on_construction(global);
    }

    auto registry::on_destructor_error() noexcept -> void {
        ::on_destructor_error(global);
    }

    auto registry::on_constructor_error() noexcept -> void {
        ::on_constructor_error(global);
    }

    auto registry::on_operator_error() noexcept -> void {
        ::on_operator_error(global);
    }

}
