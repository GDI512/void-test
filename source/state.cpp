#include <output.hpp>
#include <state.hpp>

namespace test::core {

    exit_code code = exit_code::success;

    global_struct global = {};

    auto test_struct::is_ok() const noexcept -> bool {
        return error_count == 0;
    }

    auto test_struct::is_empty() const noexcept -> bool {
        return error_count == 0 && total_count == 0;
    }

    auto object_struct::is_ok() const noexcept -> bool {
        return destroyed_count == constructed_count && destructor_error_count == 0 && constructor_error_count == 0 &&
               operator_error_count == 0;
    }

    auto object_struct::is_empty() const noexcept -> bool {
        return destroyed_count == 0 && constructed_count == 0 && destructor_error_count == 0 &&
               constructor_error_count == 0 && operator_error_count == 0;
    }

    registry::~registry() noexcept {
        const auto result = global.test_state - snapshot;
        if (result.is_ok() && !result.is_empty()) {
            global.test_state -= result;
            scope::on_registry_success(result);
        } else if (!result.is_ok()) {
            code = exit_code::failure;
            global.test_state -= result;
            scope::on_registry_error(result);
        }
    }

    registry::registry() noexcept : snapshot(global.test_state) {}

    auto registry::on_error(const char* source) noexcept -> bool {
        ++global.test_state.error_count;
        ++global.test_state.total_count;
        scope::on_error(source);
        return false;
    }

    auto registry::on_success(const char* source) noexcept -> bool {
        ++global.test_state.total_count;
        scope::on_success(source);
        return true;
    }

    auto registry::on_exception(const char* source) noexcept -> void {
        ++global.test_state.error_count;
        scope::on_exception(source);
    }

    verifier::~verifier() noexcept {
        const auto result = global.object_state - snapshot;
        if (result.is_ok() && !result.is_empty()) {
            global.object_state -= result;
            scope::on_verifier_success(result);
        } else if (!result.is_ok()) {
            code = exit_code::failure;
            global.object_state -= result;
            scope::on_verifier_error(result);
        }
    }

    verifier::verifier() noexcept : snapshot(global.object_state) {}

    auto verifier::on_destruction() noexcept -> void {
        ++global.object_state.destroyed_count;
    }

    auto verifier::on_construction() noexcept -> void {
        ++global.object_state.constructed_count;
    }

    auto verifier::on_destructor_error() noexcept -> void {
        ++global.object_state.destructor_error_count;
    }

    auto verifier::on_constructor_error() noexcept -> void {
        ++global.object_state.constructor_error_count;
    }

    auto verifier::on_operator_error() noexcept -> void {
        ++global.object_state.operator_error_count;
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
