#include <output.hpp>
#include <state.hpp>

namespace test {

    struct assert_tag {};
    struct object_tag {};
    struct error_tag {};

    static auto difference(state global, state snapshot) noexcept -> state {
        auto result = state();
        result.assert.total = global.assert.total - snapshot.assert.total;
        result.assert.error = global.assert.error - snapshot.assert.error;
        result.object.destroyed = global.object.destroyed - snapshot.object.destroyed;
        result.object.constructed = global.object.constructed - snapshot.object.constructed;
        result.error.destructor = global.error.destructor - snapshot.error.destructor;
        result.error.constructor = global.error.constructor - snapshot.error.constructor;
        result.error.assignment = global.error.assignment - snapshot.error.assignment;
        return result;
    }

    static auto restore(state& global, state snapshot) noexcept -> void {
        global.assert.total -= snapshot.assert.total;
        global.assert.error -= snapshot.assert.error;
        global.object.destroyed -= snapshot.object.destroyed;
        global.object.constructed -= snapshot.object.constructed;
        global.error.destructor -= snapshot.error.destructor;
        global.error.constructor -= snapshot.error.constructor;
        global.error.assignment -= snapshot.error.assignment;
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

    static auto empty(state result) noexcept -> bool {
        return result.assert.total == 0 && result.object.constructed == 0 && result.object.destroyed == 0;
    }

    static auto status(state result) noexcept -> bool {
        const auto assert_status = test::status(result, assert_tag());
        const auto object_status = test::status(result, object_tag());
        const auto error_status = test::status(result, error_tag());
        return assert_status && object_status && error_status;
    }

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
