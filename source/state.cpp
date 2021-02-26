#include <output.hpp>
#include <state.hpp>

namespace test {

    struct assert_tag {};
    struct object_tag {};
    struct error_tag {};

    static auto code(exit_code value) noexcept -> void {
        return_value = value;
    }

    static auto on_error(state& global) noexcept -> void {
        ++global.assert.total;
        ++global.assert.error;
    }

    static auto on_success(state& global) noexcept -> void {
        ++global.assert.total;
    }

    static auto on_destruction(state& global) noexcept -> void {
        ++global.object.destroyed;
    }

    static auto on_construction(state& global) noexcept -> void {
        ++global.object.constructed;
    }

    static auto on_destructor_error(state& global) noexcept -> void {
        ++global.error.destructor;
    }

    static auto on_constructor_error(state& global) noexcept -> void {
        ++global.error.constructor;
    }

    static auto on_operator_error(state& global) noexcept -> void {
        ++global.error.assignment;
    }

    static auto difference(state global, state snapshot, assert_tag) -> decltype(snapshot.assert) {
        auto result = decltype(snapshot.assert)();
        result.total = global.assert.total - snapshot.assert.total;
        result.error = global.assert.error - snapshot.assert.error;
        return result;
    }

    static auto difference(state global, state snapshot, object_tag) -> decltype(snapshot.object) {
        auto result = decltype(snapshot.object)();
        result.destroyed = global.object.destroyed - snapshot.object.destroyed;
        result.constructed = global.object.constructed - snapshot.object.constructed;
        return result;
    }

    static auto difference(state global, state snapshot, error_tag) -> decltype(snapshot.error) {
        auto result = decltype(snapshot.error)();
        result.destructor = global.error.destructor - snapshot.error.destructor;
        result.constructor = global.error.constructor - snapshot.error.constructor;
        result.assignment = global.error.assignment - snapshot.error.assignment;
        return result;
    }

    static auto difference(state global, state snapshot) noexcept -> state {
        auto result = state();
        result.assert = test::difference(global, snapshot, assert_tag());
        result.object = test::difference(global, snapshot, object_tag());
        result.error = test::difference(global, snapshot, error_tag());
        return result;
    }

    static auto restore(state& global, state snapshot, assert_tag) noexcept -> void {
        global.assert.total -= snapshot.assert.total;
        global.assert.error -= snapshot.assert.error;
    }

    static auto restore(state& global, state snapshot, object_tag) noexcept -> void {
        global.object.destroyed -= snapshot.object.destroyed;
        global.object.constructed -= snapshot.object.constructed;
    }

    static auto restore(state& global, state snapshot, error_tag) noexcept -> void {
        global.error.destructor -= snapshot.error.destructor;
        global.error.constructor -= snapshot.error.constructor;
        global.error.assignment -= snapshot.error.assignment;
    }

    static auto restore(state& global, state snapshot) noexcept -> void {
        test::restore(global, snapshot, assert_tag());
        test::restore(global, snapshot, object_tag());
        test::restore(global, snapshot, error_tag());
    }

    static auto status(state result, assert_tag) noexcept -> bool {
        return result.assert.error == 0;
    }

    static auto status(state result, object_tag) noexcept -> bool {
        return result.object.destroyed == result.object.constructed;
    }

    static auto status(state result, error_tag) noexcept -> bool {
        return result.error.destructor + result.error.constructor + result.error.assignment == 0;
    }

    static auto status(state result) noexcept -> bool {
        const auto assert_status = test::status(result, assert_tag());
        const auto object_status = test::status(result, object_tag());
        const auto error_status = test::status(result, error_tag());
        return assert_status && object_status && error_status;
    }

    static auto empty(state result) noexcept -> bool {
        return result.assert.total == 0 && result.object.constructed + result.object.destroyed == 0;
    }

}

namespace test {

    exit_code return_value = exit_code::success;

    state registry::global = {};

    registry::~registry() noexcept {
        const auto result = test::difference(global, snapshot);
        if (!empty() && status()) {
            output::on_unit_success(result);
            test::restore(global, snapshot);
        } else {
            output::on_unit_error(result);
            test::restore(global, snapshot);
            test::code(exit_code::failure);
        }
    }

    registry::registry() noexcept : snapshot(global) {}

    auto registry::empty() noexcept -> bool {
        const auto result = test::difference(global, snapshot);
        return test::empty(result);
    }

    auto registry::status() noexcept -> bool {
        const auto result = test::difference(global, snapshot);
        return test::status(result);
    }

    auto registry::on_error(const char* source) noexcept -> void {
        output::on_error(source);
        test::on_error(global);
    }

    auto registry::on_success(const char* source) noexcept -> void {
        output::on_success(source);
        test::on_success(global);
    }

    auto registry::on_exception(const char* source) noexcept -> void {
        output::on_exception(source);
        test::on_error(global);
    }

    auto registry::on_destruction() noexcept -> void {
        test::on_destruction(global);
    }

    auto registry::on_construction() noexcept -> void {
        test::on_construction(global);
    }

    auto registry::on_destructor_error() noexcept -> void {
        test::on_destructor_error(global);
    }

    auto registry::on_constructor_error() noexcept -> void {
        test::on_constructor_error(global);
    }

    auto registry::on_operator_error() noexcept -> void {
        test::on_operator_error(global);
    }

}
