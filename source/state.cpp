#include <output.hpp>
#include <state.hpp>

namespace test {

    exit_code code = exit_code::success;
    global_info global = {};

    registry::~registry() noexcept {
        const auto result = compute_unit_result(snapshot);
        if (error_free(result) && !empty(result)) {
            restore_global_state(result);
            scope::on_registry_success(result);
        } else if (!error_free(result)) {
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
        if (error_free(result) && !empty(result)) {
            restore_global_state(result);
            scope::on_verifier_success(result);
        } else if (!error_free(result)) {
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

    auto restore_global_state(test_info result) noexcept -> void {
        global.test_state.total_count -= result.total_count;
        global.test_state.error_count -= result.error_count;
    }

    auto restore_global_state(object_info result) noexcept -> void {
        global.object_state.destroyed_count -= result.destroyed_count;
        global.object_state.constructed_count -= result.constructed_count;
        global.object_state.destructor_error_count -= result.destructor_error_count;
        global.object_state.constructor_error_count -= result.constructor_error_count;
        global.object_state.operator_error_count -= result.operator_error_count;
    }

    auto compute_unit_result(test_info snapshot) noexcept -> test_info {
        auto result = test_info();
        result.error_count = global.test_state.error_count - snapshot.error_count;
        result.total_count = global.test_state.total_count - snapshot.total_count;
        return result;
    }

    auto compute_unit_result(object_info snapshot) noexcept -> object_info {
        auto result = object_info();
        result.destroyed_count = global.object_state.destroyed_count - snapshot.destroyed_count;
        result.constructed_count = global.object_state.constructed_count - snapshot.constructed_count;
        result.destructor_error_count = global.object_state.destructor_error_count - snapshot.destructor_error_count;
        result.constructor_error_count = global.object_state.constructor_error_count - snapshot.destructor_error_count;
        result.operator_error_count = global.object_state.operator_error_count - snapshot.destructor_error_count;
        return result;
    }

    auto empty(test_info state) noexcept -> bool {
        return state.error_count == 0 && state.total_count == 0;
    }

    auto empty(object_info state) noexcept -> bool {
        return state.destroyed_count == 0 && state.constructed_count == 0 && state.destructor_error_count == 0 &&
               state.constructor_error_count == 0 && state.operator_error_count == 0;
    }

    auto error_free(test_info state) noexcept -> bool {
        return state.error_count == 0;
    }

    auto error_free(object_info state) noexcept -> bool {
        return state.destroyed_count == state.constructed_count && state.destructor_error_count == 0 &&
               state.constructor_error_count == 0 && state.operator_error_count == 0;
    }

}
