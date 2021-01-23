#include "common.hpp"

using namespace test;

int main() {
    { cassert(core::exit_code() == core::exit_success); }
    {
        cassert(core::global_test_state.total_count == 0);
        cassert(core::global_test_state.error_count == 0);
    }
    {
        cassert(core::global_resource_state.destroyed_count == 0);
        cassert(core::global_resource_state.constructed_count == 0);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        cassert(core::on_error("") == false);
        cassert(core::global_test_state.total_count == 1);
        cassert(core::global_test_state.error_count == 1);
        cassert(core::on_success("") == true);
        cassert(core::global_test_state.total_count == 2);
        cassert(core::global_test_state.error_count == 1);
        cassert(core::on_exception("") == false);
        cassert(core::global_test_state.total_count == 2);
        cassert(core::global_test_state.error_count == 2);
    }
    {
        core::on_destruction();
        cassert(core::global_resource_state.destroyed_count == 1);
        core::on_construction();
        cassert(core::global_resource_state.constructed_count == 1);
        core::on_destructor_error();
        cassert(core::global_resource_state.destructor_error_count == 1);
        core::on_constructor_error();
        cassert(core::global_resource_state.constructor_error_count == 1);
        core::on_operator_error();
        cassert(core::global_resource_state.operator_error_count == 1);
    }
    {
        const auto x = core::test_state{7, 7};
        const auto y = core::test_state{5, 5};
        const auto z = x - y;
        cassert(z.total_count == 2);
        cassert(z.error_count == 2);
    }
    {
        const auto x = core::test_state{7, 7};
        const auto y = core::test_state{5, 5};
        const auto z = x + y;
        cassert(z.total_count == 12);
        cassert(z.error_count == 12);
    }
    {
        auto x = core::test_state{7, 7};
        const auto y = core::test_state{5, 5};
        x -= y;
        cassert(x.total_count == 2);
        cassert(x.error_count == 2);
    }
    {
        auto x = core::test_state{7, 7};
        const auto y = core::test_state{5, 5};
        x += y;
        cassert(x.total_count == 12);
        cassert(x.error_count == 12);
    }
    {
        const auto x = core::resource_state{7, 7, 7, 7, 7};
        const auto y = core::resource_state{5, 5, 5, 5, 5};
        const auto z = x - y;
        cassert(z.destroyed_count == 2);
        cassert(z.constructed_count == 2);
        cassert(z.destructor_error_count == 2);
        cassert(z.constructor_error_count == 2);
        cassert(z.operator_error_count == 2);
    }
    {
        const auto x = core::resource_state{7, 7, 7, 7, 7};
        const auto y = core::resource_state{5, 5, 5, 5, 5};
        const auto z = x + y;
        cassert(z.destroyed_count == 12);
        cassert(z.constructed_count == 12);
        cassert(z.destructor_error_count == 12);
        cassert(z.constructor_error_count == 12);
        cassert(z.operator_error_count == 12);
    }
    {
        auto x = core::resource_state{7, 7, 7, 7, 7};
        const auto y = core::resource_state{5, 5, 5, 5, 5};
        x -= y;
        cassert(x.destroyed_count == 2);
        cassert(x.constructed_count == 2);
        cassert(x.destructor_error_count == 2);
        cassert(x.constructor_error_count == 2);
        cassert(x.operator_error_count == 2);
    }
    {
        auto x = core::resource_state{7, 7, 7, 7, 7};
        const auto y = core::resource_state{5, 5, 5, 5, 5};
        x += y;
        cassert(x.destroyed_count == 12);
        cassert(x.constructed_count == 12);
        cassert(x.destructor_error_count == 12);
        cassert(x.constructor_error_count == 12);
        cassert(x.operator_error_count == 12);
    }
    {
        core::global_test_state = {};
        {
            auto tracker = core::registry();
            core::on_error("");
            core::on_success("");
            core::on_exception("");
        }
        cassert(core::global_test_state.total_count == 0);
        cassert(core::global_test_state.error_count == 0);
    }
    {
        core::global_resource_state = {};
        {
            auto tracker = core::verifier();
            core::on_destruction();
            core::on_construction();
            core::on_destructor_error();
            core::on_constructor_error();
            core::on_operator_error();
        }
        cassert(core::global_resource_state.destroyed_count == 0);
        cassert(core::global_resource_state.constructed_count == 0);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
}
