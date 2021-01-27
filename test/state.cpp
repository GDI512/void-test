#include "common.hpp"

using namespace test;

int main() {
    { cassert(core::exit_code() == core::exit_success); }
    {
        cassert(core::global.test.total_count == 0);
        cassert(core::global.test.error_count == 0);
    }
    {
        cassert(core::global.object.destroyed_count == 0);
        cassert(core::global.object.constructed_count == 0);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto state = core::test_struct{};
        cassert(core::is_ok(state));
        state.total_count += 1;
        cassert(core::is_ok(state));
        state.error_count += 1;
        cassert(!core::is_ok(state));
    }
    {
        auto state = core::object_struct{};
        cassert(core::is_ok(state));
        state.constructed_count += 1;
        state.destroyed_count += 1;
        cassert(core::is_ok(state));
        state.destroyed_count += 1;
        cassert(!core::is_ok(state));
    }
    {
        auto state = core::test_struct{};
        cassert(core::is_empty(state));
        state.total_count += 1;
        cassert(!core::is_empty(state))
    }
    {
        auto state = core::object_struct{};
        cassert(core::is_empty(state));
        state.constructed_count += 1;
        cassert(!core::is_empty(state))
    }
    {
        auto state = core::global_struct{};
        cassert(core::exit_code(state) == core::exit_success);
        core::exit_code(core::exit_failure, state);
        cassert(core::exit_code(state) == core::exit_failure);
    }
    {
        auto state = core::global_struct{};
        core::register_error(state);
        cassert(state.test.total_count == 1);
        cassert(state.test.error_count == 1);
    }
    {
        auto state = core::global_struct{};
        core::register_success(state);
        cassert(state.test.total_count == 1);
    }
    {
        auto state = core::global_struct{};
        core::register_exception(state);
        cassert(state.test.total_count == 0);
        cassert(state.test.error_count == 1);
    }
    {
        auto state = core::global_struct{};
        core::register_destruction(state);
        cassert(state.object.destroyed_count == 1);
    }
    {
        auto state = core::global_struct{};
        core::register_construction(state);
        cassert(state.object.constructed_count == 1);
    }
    {
        auto state = core::global_struct{};
        core::register_destructor_error(state);
        cassert(state.object.destructor_error_count == 1);
    }
    {
        auto state = core::global_struct{};
        core::register_constructor_error(state);
        cassert(state.object.constructor_error_count == 1);
    }
    {
        auto state = core::global_struct{};
        core::register_operator_error(state);
        cassert(state.object.operator_error_count == 1);
    }
    {
        auto state = core::global_struct{};
        cassert(core::on_error("", state) == false);
        cassert(state.test.total_count == 1);
        cassert(state.test.error_count == 1);
        cassert(core::on_success("", state) == true);
        cassert(state.test.total_count == 2);
        cassert(state.test.error_count == 1);
        cassert(core::on_exception("", state) == false);
        cassert(state.test.total_count == 2);
        cassert(state.test.error_count == 2);
    }
    {
        auto state = core::global_struct{};
        core::on_destruction(state);
        cassert(state.object.destroyed_count == 1);
        core::on_construction(state);
        cassert(state.object.constructed_count == 1);
        core::on_destructor_error(state);
        cassert(state.object.destructor_error_count == 1);
        core::on_constructor_error(state);
        cassert(state.object.constructor_error_count == 1);
        core::on_operator_error(state);
        cassert(state.object.operator_error_count == 1);
    }
    {
        const auto state = core::test_struct{7, 7};
        const auto other = core::test_struct{5, 5};
        const auto diff = state - other;
        cassert(diff.total_count == 2);
        cassert(diff.error_count == 2);
    }
    {
        const auto state = core::test_struct{7, 7};
        const auto other = core::test_struct{5, 5};
        const auto sum = state + other;
        cassert(sum.total_count == 12);
        cassert(sum.error_count == 12);
    }
    {
        auto state = core::test_struct{7, 7};
        const auto other = core::test_struct{5, 5};
        state -= other;
        cassert(state.total_count == 2);
        cassert(state.error_count == 2);
    }
    {
        auto state = core::test_struct{7, 7};
        const auto other = core::test_struct{5, 5};
        state += other;
        cassert(state.total_count == 12);
        cassert(state.error_count == 12);
    }
    {
        const auto state = core::object_struct{7, 7, 7, 7, 7};
        const auto other = core::object_struct{5, 5, 5, 5, 5};
        const auto diff = state - other;
        cassert(diff.destroyed_count == 2);
        cassert(diff.constructed_count == 2);
        cassert(diff.destructor_error_count == 2);
        cassert(diff.constructor_error_count == 2);
        cassert(diff.operator_error_count == 2);
    }
    {
        const auto state = core::object_struct{7, 7, 7, 7, 7};
        const auto other = core::object_struct{5, 5, 5, 5, 5};
        const auto sum = state + other;
        cassert(sum.destroyed_count == 12);
        cassert(sum.constructed_count == 12);
        cassert(sum.destructor_error_count == 12);
        cassert(sum.constructor_error_count == 12);
        cassert(sum.operator_error_count == 12);
    }
    {
        auto state = core::object_struct{7, 7, 7, 7, 7};
        const auto other = core::object_struct{5, 5, 5, 5, 5};
        state -= other;
        cassert(state.destroyed_count == 2);
        cassert(state.constructed_count == 2);
        cassert(state.destructor_error_count == 2);
        cassert(state.constructor_error_count == 2);
        cassert(state.operator_error_count == 2);
    }
    {
        auto state = core::object_struct{7, 7, 7, 7, 7};
        const auto other = core::object_struct{5, 5, 5, 5, 5};
        state += other;
        cassert(state.destroyed_count == 12);
        cassert(state.constructed_count == 12);
        cassert(state.destructor_error_count == 12);
        cassert(state.constructor_error_count == 12);
        cassert(state.operator_error_count == 12);
    }
    {
        auto state = core::global_struct{};
        {
            auto tracker = core::registry(state);
            core::on_error("", state);
            core::on_success("", state);
            core::on_exception("", state);
        }
        cassert(state.test.total_count == 0);
        cassert(state.test.error_count == 0);
    }
    {
        auto state = core::global_struct{};
        {
            auto tracker = core::verifier(state);
            core::on_destruction(state);
            core::on_construction(state);
            core::on_destructor_error(state);
            core::on_constructor_error(state);
            core::on_operator_error(state);
        }
        cassert(state.object.destroyed_count == 0);
        cassert(state.object.constructed_count == 0);
        cassert(state.object.destructor_error_count == 0);
        cassert(state.object.constructor_error_count == 0);
        cassert(state.object.operator_error_count == 0);
    }
}
