#include <output.hpp>
#include <state.hpp>

namespace test::core {

    int global_exit_code = exit_success;
    test_state global_test_state = {};
    resource_state global_resource_state = {};

    static auto is_ok(test_state state) noexcept -> bool {
        return state.error_count == 0;
    }

    static auto is_ok(resource_state state) noexcept -> bool {
        return state.destroyed_count == state.constructed_count && state.destructor_error_count == 0 &&
               state.constructor_error_count == 0 && state.operator_error_count == 0;
    }

    static auto is_empty(test_state state) noexcept -> bool {
        return state.error_count == 0 && state.total_count == 0;
    }

    static auto is_empty(resource_state state) noexcept -> bool {
        return state.destroyed_count == 0 && state.constructed_count == 0 && state.destructor_error_count == 0 &&
               state.constructor_error_count == 0 && state.operator_error_count == 0;
    }

    static auto exit_code(int value) noexcept -> void {
        global_exit_code = value;
    }

    static auto register_error() noexcept -> void {
        ++global_test_state.total_count;
        ++global_test_state.error_count;
    }

    static auto register_success() noexcept -> void {
        ++global_test_state.total_count;
    }

    static auto register_exception() noexcept -> void {
        ++global_test_state.error_count;
    }

    static auto register_destruction() noexcept -> void {
        ++global_resource_state.destroyed_count;
    }

    static auto register_construction() noexcept -> void {
        ++global_resource_state.constructed_count;
    }

    static auto register_destructor_error() noexcept -> void {
        ++global_resource_state.destructor_error_count;
    }

    static auto register_constructor_error() noexcept -> void {
        ++global_resource_state.constructor_error_count;
    }

    static auto register_operator_error() noexcept -> void {
        ++global_resource_state.operator_error_count;
    }

    registry::~registry() noexcept {
        const auto delta = global_test_state - snapshot;
        if (is_ok(delta) && !is_empty(delta)) {
            print_registry_success(delta);
        } else if (!is_ok(delta)) {
            exit_code(exit_failure);
            print_registry_error(delta);
        }
        global_test_state -= delta;
    }

    registry::registry() noexcept : snapshot(global_test_state) {}

    verifier::~verifier() noexcept {
        const auto delta = global_resource_state - snapshot;
        if (is_ok(delta) && !is_empty(delta)) {
            print_verifier_success(delta);
        } else if (!is_ok(delta)) {
            exit_code(exit_failure);
            print_verifier_error(delta);
        }
        global_resource_state -= delta;
    }

    verifier::verifier() noexcept : snapshot(global_resource_state) {}

    auto exit_code() noexcept -> int {
        return global_exit_code;
    }

    auto on_error(string source) noexcept -> bool {
        register_error();
        print_error(source);
        return false;
    }

    auto on_success(string source) noexcept -> bool {
        register_success();
        print_success(source);
        return true;
    }

    auto on_exception(string source) noexcept -> bool {
        register_exception();
        print_exception(source);
        return false;
    }

    auto on_destruction() noexcept -> void {
        register_destruction();
    }

    auto on_construction() noexcept -> void {
        register_construction();
    }

    auto on_destructor_error() noexcept -> void {
        register_destructor_error();
    }

    auto on_constructor_error() noexcept -> void {
        register_constructor_error();
    }

    auto on_operator_error() noexcept -> void {
        register_operator_error();
    }

    auto operator+(test_state left, test_state right) noexcept -> test_state {
        return {left.total_count + right.total_count, left.error_count + right.error_count};
    }

    auto operator-(test_state left, test_state right) noexcept -> test_state {
        return {left.total_count - right.total_count, left.error_count - right.error_count};
    }

    auto operator+=(test_state& left, test_state right) noexcept -> test_state& {
        left.total_count += right.total_count;
        left.error_count += right.error_count;
        return left;
    }

    auto operator-=(test_state& left, test_state right) noexcept -> test_state& {
        left.total_count -= right.total_count;
        left.error_count -= right.error_count;
        return left;
    }

    auto operator+(resource_state left, resource_state right) noexcept -> resource_state {
        return {
            left.destroyed_count + right.destroyed_count,
            left.constructed_count + right.constructed_count,
            left.destructor_error_count + right.destructor_error_count,
            left.constructor_error_count + right.constructor_error_count,
            left.operator_error_count + right.operator_error_count,
        };
    }

    auto operator-(resource_state left, resource_state right) noexcept -> resource_state {
        return {
            left.destroyed_count - right.destroyed_count,
            left.constructed_count - right.constructed_count,
            left.destructor_error_count - right.destructor_error_count,
            left.constructor_error_count - right.constructor_error_count,
            left.operator_error_count - right.operator_error_count,
        };
    }

    auto operator+=(resource_state& left, resource_state right) noexcept -> resource_state& {
        left.destroyed_count += right.destroyed_count;
        left.constructed_count += right.constructed_count;
        left.destructor_error_count += right.destructor_error_count;
        left.constructor_error_count += right.constructor_error_count;
        left.operator_error_count += right.operator_error_count;
        return left;
    }

    auto operator-=(resource_state& left, resource_state right) noexcept -> resource_state& {
        left.destroyed_count -= right.destroyed_count;
        left.constructed_count -= right.constructed_count;
        left.destructor_error_count -= right.destructor_error_count;
        left.constructor_error_count -= right.constructor_error_count;
        left.operator_error_count -= right.operator_error_count;
        return left;
    }

}
