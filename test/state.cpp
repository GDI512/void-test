#include "common.hpp"

using namespace test;

int main() {
    {
        const auto code = core::code;
        cassert(code == core::exit_code::success);
    }
    {
        cassert(core::global.test_state.total_count == 0);
        cassert(core::global.test_state.error_count == 0);
    }
    {
        cassert(core::global.object_state.destroyed_count == 0);
        cassert(core::global.object_state.constructed_count == 0);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto state = core::test_struct{};
        cassert(state.is_ok());
        state.total_count += 1;
        cassert(state.is_ok());
        state.error_count += 1;
        cassert(!state.is_ok());
    }
    {
        auto state = core::object_struct{};
        cassert(state.is_ok());
        state.constructed_count += 1;
        state.destroyed_count += 1;
        cassert(state.is_ok());
        state.destroyed_count += 1;
        cassert(!state.is_ok());
    }
    {
        auto state = core::test_struct{};
        cassert(state.is_empty());
        state.total_count += 1;
        cassert(!state.is_empty())
    }
    {
        auto state = core::object_struct{};
        cassert(state.is_empty());
        state.constructed_count += 1;
        cassert(!state.is_empty())
    }
    {
        core::global = core::global_struct{};
        core::registry::on_error("");
        cassert(core::global.test_state.total_count == 1);
        cassert(core::global.test_state.error_count == 1);
    }
    {
        core::global = core::global_struct{};
        core::registry::on_success("");
        cassert(core::global.test_state.total_count == 1);
        cassert(core::global.test_state.error_count == 0);
    }
    {
        core::global = core::global_struct{};
        core::registry::on_exception("");
        cassert(core::global.test_state.total_count == 0);
        cassert(core::global.test_state.error_count == 1);
    }
    {
        core::global = core::global_struct{};
        core::verifier::on_destruction();
        cassert(core::global.object_state.destroyed_count == 1);
    }
    {
        core::global = core::global_struct{};
        core::verifier::on_construction();
        cassert(core::global.object_state.constructed_count == 1);
    }
    {
        core::global = core::global_struct{};
        core::verifier::on_destructor_error();
        cassert(core::global.object_state.destructor_error_count == 1);
    }
    {
        core::global = core::global_struct{};
        core::verifier::on_constructor_error();
        cassert(core::global.object_state.constructor_error_count == 1);
    }
    {
        core::global = core::global_struct{};
        core::verifier::on_operator_error();
        cassert(core::global.object_state.operator_error_count == 1);
    }
    {
        core::global = core::global_struct{};
        cassert(core::registry::on_error("") == false);
        cassert(core::global.test_state.total_count == 1);
        cassert(core::global.test_state.error_count == 1);
        cassert(core::registry::on_success("") == true);
        cassert(core::global.test_state.total_count == 2);
        cassert(core::global.test_state.error_count == 1);
        core::registry::on_exception("");
        cassert(core::global.test_state.total_count == 2);
        cassert(core::global.test_state.error_count == 2);
    }
    {
        core::global = core::global_struct{};
        core::verifier::on_destruction();
        cassert(core::global.object_state.destroyed_count == 1);
        core::verifier::on_construction();
        cassert(core::global.object_state.constructed_count == 1);
        core::verifier::on_destructor_error();
        cassert(core::global.object_state.destructor_error_count == 1);
        core::verifier::on_constructor_error();
        cassert(core::global.object_state.constructor_error_count == 1);
        core::verifier::on_operator_error();
        cassert(core::global.object_state.operator_error_count == 1);
    }
    {
        core::global = core::global_struct{};
        {
            auto tracker = core::registry();
            core::registry::on_error("");
            core::registry::on_success("");
            core::registry::on_exception("");
        }
        cassert(core::code == core::exit_code::failure);
        cassert(core::global.test_state.total_count == 0);
        cassert(core::global.test_state.error_count == 0);
    }
    {
        core::global = core::global_struct{};
        {
            auto tracker = core::verifier();
            core::verifier::on_destruction();
            core::verifier::on_construction();
            core::verifier::on_destructor_error();
            core::verifier::on_constructor_error();
            core::verifier::on_operator_error();
        }
        cassert(core::code == core::exit_code::failure);
        cassert(core::global.object_state.destroyed_count == 0);
        cassert(core::global.object_state.constructed_count == 0);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 0);
    }
}
