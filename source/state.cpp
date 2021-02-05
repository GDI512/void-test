#include <output.hpp>
#include <state.hpp>

namespace test::core {

    global_struct global = {};

    registry::~registry() noexcept {
        const auto difference = global.test - snapshot;
        if (is_ok(difference) && !is_empty(difference)) {
            scope::on_registry_success(difference);
        } else if (!is_ok(difference)) {
            exit_code(exit_failure);
            scope::on_registry_error(difference);
        }
        global.test -= difference;
    }

    registry::registry() noexcept : snapshot(global.test) {}

    auto registry::on_error(const char* source) noexcept -> bool {
        ++global.test.error_count;
        ++global.test.total_count;
        scope::on_error(source);
        return false;
    }

    auto registry::on_success(const char* source) noexcept -> bool {
        ++global.test.total_count;
        scope::on_success(source);
        return true;
    }

    auto registry::on_exception(const char* source) noexcept -> void {
        ++global.test.error_count;
        scope::on_exception(source);
    }

    verifier::~verifier() noexcept {
        const auto difference = global.object - snapshot;
        if (is_ok(difference) && !is_empty(difference)) {
            scope::on_verifier_success(difference);
        } else if (!is_ok(difference)) {
            exit_code(exit_failure);
            scope::on_verifier_error(difference);
        }
        global.object -= difference;
    }

    verifier::verifier() noexcept : snapshot(global.object) {}

    auto verifier::on_destruction() noexcept -> void {
        ++global.object.destroyed_count;
    }

    auto verifier::on_construction() noexcept -> void {
        ++global.object.constructed_count;
    }

    auto verifier::on_destructor_error() noexcept -> void {
        ++global.object.destructor_error_count;
    }

    auto verifier::on_constructor_error() noexcept -> void {
        ++global.object.constructor_error_count;
    }

    auto verifier::on_operator_error() noexcept -> void {
        ++global.object.operator_error_count;
    }

    auto is_ok(test_struct state) noexcept -> bool {
        return state.error_count == 0;
    }

    auto is_ok(object_struct state) noexcept -> bool {
        return state.destroyed_count == state.constructed_count && state.destructor_error_count == 0 &&
               state.constructor_error_count == 0 && state.operator_error_count == 0;
    }

    auto is_empty(test_struct state) noexcept -> bool {
        return state.error_count == 0 && state.total_count == 0;
    }

    auto is_empty(object_struct state) noexcept -> bool {
        return state.destroyed_count == 0 && state.constructed_count == 0 && state.destructor_error_count == 0 &&
               state.constructor_error_count == 0 && state.operator_error_count == 0;
    }

    auto exit_code() noexcept -> int {
        return global.info.exit_code;
    }

    auto exit_code(int code) noexcept -> void {
        global.info.exit_code = code;
    }

    auto operator+(test_struct left, test_struct right) noexcept -> test_struct {
        return {left.total_count + right.total_count, left.error_count + right.error_count};
    }

    auto operator-(test_struct left, test_struct right) noexcept -> test_struct {
        return {left.total_count - right.total_count, left.error_count - right.error_count};
    }

    auto operator+=(test_struct& left, test_struct right) noexcept -> test_struct& {
        left.total_count += right.total_count;
        left.error_count += right.error_count;
        return left;
    }

    auto operator-=(test_struct& left, test_struct right) noexcept -> test_struct& {
        left.total_count -= right.total_count;
        left.error_count -= right.error_count;
        return left;
    }

    auto operator+(object_struct left, object_struct right) noexcept -> object_struct {
        return {
            left.destroyed_count + right.destroyed_count,
            left.constructed_count + right.constructed_count,
            left.destructor_error_count + right.destructor_error_count,
            left.constructor_error_count + right.constructor_error_count,
            left.operator_error_count + right.operator_error_count,
        };
    }

    auto operator-(object_struct left, object_struct right) noexcept -> object_struct {
        return {
            left.destroyed_count - right.destroyed_count,
            left.constructed_count - right.constructed_count,
            left.destructor_error_count - right.destructor_error_count,
            left.constructor_error_count - right.constructor_error_count,
            left.operator_error_count - right.operator_error_count,
        };
    }

    auto operator+=(object_struct& left, object_struct right) noexcept -> object_struct& {
        left.destroyed_count += right.destroyed_count;
        left.constructed_count += right.constructed_count;
        left.destructor_error_count += right.destructor_error_count;
        left.constructor_error_count += right.constructor_error_count;
        left.operator_error_count += right.operator_error_count;
        return left;
    }

    auto operator-=(object_struct& left, object_struct right) noexcept -> object_struct& {
        left.destroyed_count -= right.destroyed_count;
        left.constructed_count -= right.constructed_count;
        left.destructor_error_count -= right.destructor_error_count;
        left.constructor_error_count -= right.constructor_error_count;
        left.operator_error_count -= right.operator_error_count;
        return left;
    }

}
