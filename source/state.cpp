#include <output.hpp>
#include <state.hpp>

namespace {

    using namespace test::core;

    auto operator-(state_array left, state_array right) noexcept -> state_array {
        auto array = state_array();
        for (auto i = 0u; i < left.size(); i++)
            array[i] = left[i] - right[i];
        return array;
    }

    auto operator-=(state_array& left, state_array right) noexcept -> state_array& {
        for (auto i = 0u; i < left.size(); i++)
            left[i] -= right[i];
        return left;
    }

}

namespace test::core {

    exit_code registry::code = {};
    state_array registry::global = {};

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

    auto registry::data() noexcept -> state_array {
        return global - snapshot;
    }

    auto registry::empty() noexcept -> bool {
        const auto result = global - snapshot;
        return result[state::checks] + result[state::constructors] + result[state::destructors] == 0;
    }

    auto registry::status() noexcept -> bool {
        const auto result = global - snapshot;
        return result[state::errors] == 0 &&
            result[state::destructors] == result[state::constructors] &&
                result[state::destructor_errors] + result[state::constructor_errors] + result[state::assignment_errors] == 0;
    }

    auto registry::on_exit() noexcept -> int {
        return code;
    }

    auto registry::on_error() noexcept -> void {
        ++global[state::checks];
        ++global[state::errors];
    }

    auto registry::on_success() noexcept -> void {
        ++global[state::checks];
    }

    auto registry::on_exception() noexcept -> void {
        ++global[state::checks];
        ++global[state::errors];
    }

    auto registry::on_destruction() noexcept -> void {
        ++global[state::destructors];
    }

    auto registry::on_construction() noexcept -> void {
        ++global[state::constructors];
    }

    auto registry::on_destructor_error() noexcept -> void {
        ++global[state::destructor_errors];
    }

    auto registry::on_constructor_error() noexcept -> void {
        ++global[state::constructor_errors];
    }

    auto registry::on_operator_error() noexcept -> void {
        ++global[state::assignment_errors];
    }

}
