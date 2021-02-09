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
        const auto result = compute_unit_result(snapshot);
        if (result.is_ok() && !result.is_empty()) {
            restore_global_state(result);
            scope::on_registry_success(result);
        } else if (!result.is_ok()) {
            code = exit_code::failure;
            restore_global_state(result);
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
        const auto result = compute_unit_result(snapshot);
        if (result.is_ok() && !result.is_empty()) {
            restore_global_state(result);
            scope::on_verifier_success(result);
        } else if (!result.is_ok()) {
            code = exit_code::failure;
            restore_global_state(result);
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

    auto restore_global_state(test_struct result) noexcept -> void {
        global.test_state.total_count -= result.total_count;
        global.test_state.error_count -= result.error_count;
    }

    auto restore_global_state(object_struct result) noexcept -> void {
        global.object_state.destroyed_count -= result.destroyed_count;
        global.object_state.constructed_count -= result.constructed_count;
        global.object_state.destructor_error_count -= result.destructor_error_count;
        global.object_state.constructor_error_count -= result.constructor_error_count;
        global.object_state.operator_error_count -= result.operator_error_count;
    }

    auto compute_unit_result(test_struct snapshot) noexcept -> test_struct {
        auto result = test_struct();
        result.error_count = global.test_state.error_count - snapshot.error_count;
        result.total_count = global.test_state.total_count - snapshot.total_count;
        return result;
    }

    auto compute_unit_result(object_struct snapshot) noexcept -> object_struct {
        auto result = object_struct();
        result.destroyed_count = global.object_state.destroyed_count - snapshot.destroyed_count;
        result.constructed_count = global.object_state.constructed_count - snapshot.constructed_count;
        result.destructor_error_count = global.object_state.destructor_error_count - snapshot.destructor_error_count;
        result.constructor_error_count = global.object_state.constructor_error_count - snapshot.destructor_error_count;
        result.operator_error_count = global.object_state.operator_error_count - snapshot.destructor_error_count;
        return result;
    }

}
