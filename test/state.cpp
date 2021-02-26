#include "common.hpp"

using namespace test;

int main() {
    {
        const auto code = core::code;
        CASSERT(code == core::exit_code::success);
    }
    {
        CASSERT(core::global.test_state.total_count == 0);
        CASSERT(core::global.test_state.error_count == 0);
    }
    {
        CASSERT(core::global.object_state.destroyed_count == 0);
        CASSERT(core::global.object_state.constructed_count == 0);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto state = core::test_info{};
        CASSERT(error_free(state));
        state.total_count += 1;
        CASSERT(error_free(state));
        state.error_count += 1;
        CASSERT(!error_free(state));
    }
    {
        auto state = core::object_info{};
        CASSERT(error_free(state));
        state.constructed_count += 1;
        state.destroyed_count += 1;
        CASSERT(error_free(state));
        state.destroyed_count += 1;
        CASSERT(!error_free(state));
    }
    {
        auto state = core::test_info{};
        CASSERT(empty(state));
        state.total_count += 1;
        CASSERT(!empty(state))
    }
    {
        auto state = core::object_info{};
        CASSERT(empty(state));
        state.constructed_count += 1;
        CASSERT(!empty(state))
    }
    {
        core::global = core::global_info{};
        core::registry::on_error("");
        CASSERT(core::global.test_state.total_count == 1);
        CASSERT(core::global.test_state.error_count == 1);
    }
    {
        core::global = core::global_info{};
        core::registry::on_success("");
        CASSERT(core::global.test_state.total_count == 1);
        CASSERT(core::global.test_state.error_count == 0);
    }
    {
        core::global = core::global_info{};
        core::registry::on_exception("");
        CASSERT(core::global.test_state.total_count == 0);
        CASSERT(core::global.test_state.error_count == 1);
    }
    {
        core::global = core::global_info{};
        core::verifier::on_destruction();
        CASSERT(core::global.object_state.destroyed_count == 1);
    }
    {
        core::global = core::global_info{};
        core::verifier::on_construction();
        CASSERT(core::global.object_state.constructed_count == 1);
    }
    {
        core::global = core::global_info{};
        core::verifier::on_destructor_error();
        CASSERT(core::global.object_state.destructor_error_count == 1);
    }
    {
        core::global = core::global_info{};
        core::verifier::on_constructor_error();
        CASSERT(core::global.object_state.constructor_error_count == 1);
    }
    {
        core::global = core::global_info{};
        core::verifier::on_operator_error();
        CASSERT(core::global.object_state.operator_error_count == 1);
    }
    {
        core::global = core::global_info{};
        CASSERT(core::registry::on_error("") == false);
        CASSERT(core::global.test_state.total_count == 1);
        CASSERT(core::global.test_state.error_count == 1);
        CASSERT(core::registry::on_success("") == true);
        CASSERT(core::global.test_state.total_count == 2);
        CASSERT(core::global.test_state.error_count == 1);
        core::registry::on_exception("");
        CASSERT(core::global.test_state.total_count == 2);
        CASSERT(core::global.test_state.error_count == 2);
    }
    {
        core::global = core::global_info{};
        core::verifier::on_destruction();
        CASSERT(core::global.object_state.destroyed_count == 1);
        core::verifier::on_construction();
        CASSERT(core::global.object_state.constructed_count == 1);
        core::verifier::on_destructor_error();
        CASSERT(core::global.object_state.destructor_error_count == 1);
        core::verifier::on_constructor_error();
        CASSERT(core::global.object_state.constructor_error_count == 1);
        core::verifier::on_operator_error();
        CASSERT(core::global.object_state.operator_error_count == 1);
    }
    {
        core::global = core::global_info{};
        {
            auto tracker = core::registry();
            core::registry::on_error("");
            core::registry::on_success("");
            core::registry::on_exception("");
        }
        CASSERT(core::code == core::exit_code::failure);
        CASSERT(core::global.test_state.total_count == 0);
        CASSERT(core::global.test_state.error_count == 0);
    }
    {
        core::global = core::global_info{};
        {
            auto tracker = core::verifier();
            core::verifier::on_destruction();
            core::verifier::on_construction();
            core::verifier::on_destructor_error();
            core::verifier::on_constructor_error();
            core::verifier::on_operator_error();
        }
        CASSERT(core::code == core::exit_code::failure);
        CASSERT(core::global.object_state.destroyed_count == 0);
        CASSERT(core::global.object_state.constructed_count == 0);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
}
