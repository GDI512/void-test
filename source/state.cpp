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
        if (status() && !empty()) {
            const auto diff = result();
            output::on_unit_success(diff);
            global -= diff;
        } else if (!status() && !empty()) {
            const auto diff = result();
            output::on_unit_error(diff);
            global -= diff;
            code = exit_code::failure;
        }
    }

    registry::registry() noexcept : snapshot(global) {}

    auto registry::empty() const noexcept -> bool {
        const auto data = global - snapshot;
        return data[state::checks] + data[state::constructors] + data[state::destructors] == 0;
    }

    auto registry::status() const noexcept -> bool {
        const auto data = global - snapshot;
        return data[state::errors] == 0 &&
            data[state::destructors] == data[state::constructors] &&
                data[state::destructor_errors] + data[state::constructor_errors] + data[state::assignment_errors] == 0;
    }

    auto registry::result() const noexcept -> state_array {
        return global - snapshot;
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
