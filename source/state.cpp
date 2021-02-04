#include <output.hpp>
#include <state.hpp>

namespace test::core {

    global_struct global = {};

    registry::~registry() noexcept {
        const auto diff = state.test - snapshot;
        if (is_ok(diff) && !is_empty(diff)) {
            print_registry_success(diff);
        } else if (!is_ok(diff)) {
            exit_code(exit_failure);
            print_registry_error(diff);
        }
        state.test -= diff;
    }

    registry::registry(global_struct& state) noexcept : snapshot(global.test), state(state) {}

    verifier::~verifier() noexcept {
        const auto diff = state.object - snapshot;
        if (is_ok(diff) && !is_empty(diff)) {
            print_verifier_success(diff);
        } else if (!is_ok(diff)) {
            exit_code(exit_failure);
            print_verifier_error(diff);
        }
        state.object -= diff;
    }

    verifier::verifier(global_struct& state) noexcept : snapshot(global.object), state(state) {}

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

    auto exit_code(global_struct state) noexcept -> int {
        return state.info.exit_code;
    }

    auto exit_code(int code, global_struct& state) noexcept -> void {
        state.info.exit_code = code;
    }

    auto register_error(global_struct& state) noexcept -> void {
        ++state.test.total_count;
        ++state.test.error_count;
    }

    auto register_success(global_struct& state) noexcept -> void {
        ++state.test.total_count;
    }

    auto register_exception(global_struct& state) noexcept -> void {
        ++state.test.error_count;
    }

    auto register_destruction(global_struct& state) noexcept -> void {
        ++state.object.destroyed_count;
    }

    auto register_construction(global_struct& state) noexcept -> void {
        ++state.object.constructed_count;
    }

    auto register_destructor_error(global_struct& state) noexcept -> void {
        ++state.object.destructor_error_count;
    }

    auto register_constructor_error(global_struct& state) noexcept -> void {
        ++state.object.constructor_error_count;
    }

    auto register_operator_error(global_struct& state) noexcept -> void {
        ++state.object.operator_error_count;
    }

    auto on_error(const char* source, global_struct& state) noexcept -> bool {
        register_error(state);
        print_error(source);
        return false;
    }

    auto on_success(const char* source, global_struct& state) noexcept -> bool {
        register_success(state);
        print_success(source);
        return true;
    }

    auto on_exception(const char* source, global_struct& state) noexcept -> bool {
        register_exception(state);
        print_exception(source);
        return false;
    }

    auto on_destruction(global_struct& state) noexcept -> void {
        register_destruction(state);
    }

    auto on_construction(global_struct& state) noexcept -> void {
        register_construction(state);
    }

    auto on_destructor_error(global_struct& state) noexcept -> void {
        register_destructor_error(state);
    }

    auto on_constructor_error(global_struct& state) noexcept -> void {
        register_constructor_error(state);
    }

    auto on_operator_error(global_struct& state) noexcept -> void {
        register_operator_error(state);
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
