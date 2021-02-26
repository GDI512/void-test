#include "common.hpp"

int main() {
    {
        const auto code = test::code;
        CASSERT(code == test::exit_code::success);
    }
    {
        CASSERT(test::global.test_state.total_count == 0);
        CASSERT(test::global.test_state.error_count == 0);
    }
    {
        CASSERT(test::global.object_state.destroyed_count == 0);
        CASSERT(test::global.object_state.constructed_count == 0);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto state = test::test_info{};
        CASSERT(error_free(state));
        state.total_count += 1;
        CASSERT(error_free(state));
        state.error_count += 1;
        CASSERT(!error_free(state));
    }
    {
        auto state = test::object_info{};
        CASSERT(error_free(state));
        state.constructed_count += 1;
        state.destroyed_count += 1;
        CASSERT(error_free(state));
        state.destroyed_count += 1;
        CASSERT(!error_free(state));
    }
    {
        auto state = test::test_info{};
        CASSERT(empty(state));
        state.total_count += 1;
        CASSERT(!empty(state))
    }
    {
        auto state = test::object_info{};
        CASSERT(empty(state));
        state.constructed_count += 1;
        CASSERT(!empty(state))
    }
    {
        test::global = test::global_info{};
        test::registry::on_error("");
        CASSERT(test::global.test_state.total_count == 1);
        CASSERT(test::global.test_state.error_count == 1);
    }
    {
        test::global = test::global_info{};
        test::registry::on_success("");
        CASSERT(test::global.test_state.total_count == 1);
        CASSERT(test::global.test_state.error_count == 0);
    }
    {
        test::global = test::global_info{};
        test::registry::on_exception("");
        CASSERT(test::global.test_state.total_count == 0);
        CASSERT(test::global.test_state.error_count == 1);
    }
    {
        test::global = test::global_info{};
        test::verifier::on_destruction();
        CASSERT(test::global.object_state.destroyed_count == 1);
    }
    {
        test::global = test::global_info{};
        test::verifier::on_construction();
        CASSERT(test::global.object_state.constructed_count == 1);
    }
    {
        test::global = test::global_info{};
        test::verifier::on_destructor_error();
        CASSERT(test::global.object_state.destructor_error_count == 1);
    }
    {
        test::global = test::global_info{};
        test::verifier::on_constructor_error();
        CASSERT(test::global.object_state.constructor_error_count == 1);
    }
    {
        test::global = test::global_info{};
        test::verifier::on_operator_error();
        CASSERT(test::global.object_state.operator_error_count == 1);
    }
    {
        test::global = test::global_info{};
        CASSERT(test::registry::on_error("") == false);
        CASSERT(test::global.test_state.total_count == 1);
        CASSERT(test::global.test_state.error_count == 1);
        CASSERT(test::registry::on_success("") == true);
        CASSERT(test::global.test_state.total_count == 2);
        CASSERT(test::global.test_state.error_count == 1);
        test::registry::on_exception("");
        CASSERT(test::global.test_state.total_count == 2);
        CASSERT(test::global.test_state.error_count == 2);
    }
    {
        test::global = test::global_info{};
        test::verifier::on_destruction();
        CASSERT(test::global.object_state.destroyed_count == 1);
        test::verifier::on_construction();
        CASSERT(test::global.object_state.constructed_count == 1);
        test::verifier::on_destructor_error();
        CASSERT(test::global.object_state.destructor_error_count == 1);
        test::verifier::on_constructor_error();
        CASSERT(test::global.object_state.constructor_error_count == 1);
        test::verifier::on_operator_error();
        CASSERT(test::global.object_state.operator_error_count == 1);
    }
    {
        test::global = test::global_info{};
        {
            auto tracker = test::registry();
            test::registry::on_error("");
            test::registry::on_success("");
            test::registry::on_exception("");
        }
        CASSERT(test::code == test::exit_code::failure);
        CASSERT(test::global.test_state.total_count == 0);
        CASSERT(test::global.test_state.error_count == 0);
    }
    {
        test::global = test::global_info{};
        {
            auto tracker = test::verifier();
            test::verifier::on_destruction();
            test::verifier::on_construction();
            test::verifier::on_destructor_error();
            test::verifier::on_constructor_error();
            test::verifier::on_operator_error();
        }
        CASSERT(test::code == test::exit_code::failure);
        CASSERT(test::global.object_state.destroyed_count == 0);
        CASSERT(test::global.object_state.constructed_count == 0);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
}
