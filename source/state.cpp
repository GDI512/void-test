#include <output.hpp>
#include <state.hpp>

namespace test::core {

    exit_code code = {};

    state registry::global = {};

    registry::~registry() noexcept {
        const auto result = global - snapshot;
        if (!empty() && status()) {
            output::on_unit_success(result);
            global -= result;
        } else {
            output::on_unit_error(result);
            global -= result;
            code = exit_code::failure;
        }
    }

    registry::registry() noexcept : snapshot(global) {}

    auto registry::empty() noexcept -> bool {
        const auto result = global - snapshot;
        return result.total_check_count + result.constructed_count + result.destroyed_count == 0;
    }

    auto registry::status() noexcept -> bool {
        const auto result = global - snapshot;
        return result.check_error_count == 0 &&
            result.destroyed_count == result.constructed_count &&
                result.destructor_error_count + result.constructor_error_count + result.assignment_error_count == 0;
    }

    auto registry::on_error() noexcept -> void {
        ++global.total_check_count;
        ++global.check_error_count;
    }

    auto registry::on_success() noexcept -> void {
        ++global.total_check_count;
    }

    auto registry::on_exception() noexcept -> void {
        ++global.total_check_count;
        ++global.check_error_count;
    }

    auto registry::on_destruction() noexcept -> void {
        ++global.destroyed_count;
    }

    auto registry::on_construction() noexcept -> void {
        ++global.constructed_count;
    }

    auto registry::on_destructor_error() noexcept -> void {
        ++global.destructor_error_count;
    }

    auto registry::on_constructor_error() noexcept -> void {
        ++global.constructor_error_count;
    }

    auto registry::on_operator_error() noexcept -> void {
        ++global.assignment_error_count;
    }

    auto operator-(state left, state right) noexcept -> state {
        return {
            left.total_check_count - right.total_check_count,
            left.check_error_count - right.check_error_count,
            left.destroyed_count - right.destroyed_count,
            left.constructed_count - right.constructed_count,
            left.destructor_error_count - right.destructor_error_count,
            left.constructor_error_count - right.constructor_error_count,
            left.assignment_error_count - right.assignment_error_count
        };
    }

    auto operator-=(state& left, state right) noexcept -> state& {
        left.total_check_count -= right.total_check_count;
        left.check_error_count -= right.check_error_count;
        left.destroyed_count -= right.destroyed_count;
        left.constructed_count -= right.constructed_count;
        left.destructor_error_count -= right.destructor_error_count;
        left.constructor_error_count -= right.constructor_error_count;
        left.assignment_error_count -= right.assignment_error_count;
        return left;
    }

}
