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
            global -= difference();
        } else if (!status()) {
            global -= difference();
            code = exit_code::failure;
        }
    }

    registry::registry() noexcept : snapshot(global) {}

    auto registry::difference() const noexcept -> state_array {
        return global - snapshot;
    }

    auto registry::empty() const noexcept -> bool {
        const auto data = global - snapshot;
        return data[state::check] + data[state::ctor] + data[state::dtor] + data[state::operr] == 0;
    }

    auto registry::status() const noexcept -> bool {
        const auto data = global - snapshot;
        return data[state::error] == 0 && data[state::dtor] == data[state::ctor] &&
            data[state::dterr] + data[state::cterr] + data[state::operr] == 0;
    }

    auto registry::on_exit() noexcept -> int {
        return code;
    }

    auto registry::on_error() noexcept -> void {
        ++global[state::check];
        ++global[state::error];
    }

    auto registry::on_success() noexcept -> void {
        ++global[state::check];
    }

    auto registry::on_exception() noexcept -> void {
        ++global[state::check];
        ++global[state::error];
    }

    auto registry::on_destruction() noexcept -> void {
        ++global[state::dtor];
    }

    auto registry::on_construction() noexcept -> void {
        ++global[state::ctor];
    }

    auto registry::on_destructor_error() noexcept -> void {
        ++global[state::dterr];
    }

    auto registry::on_constructor_error() noexcept -> void {
        ++global[state::cterr];
    }

    auto registry::on_operator_error() noexcept -> void {
        ++global[state::operr];
    }

}
