#include "common.hpp"

int main() {
    {
        cassert(test::return_value == test::exit_code::success);
    }
    {
        auto registry = test::registry();
        cassert(registry.empty());
        cassert(registry.status());
    }
    {
        auto registry = test::registry();
        test::registry::on_error("");
        cassert(!registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::registry();
        test::registry::on_success("");
        cassert(!registry.empty());
        cassert(registry.status());
    }
    {
        auto registry = test::registry();
        test::registry::on_exception("");
        cassert(!registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::registry();
        test::registry::on_destruction();
        cassert(!registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::registry();
        test::registry::on_destruction();
        test::registry::on_construction();
        cassert(!registry.empty());
        cassert(registry.status());
    }
    {
        auto registry = test::registry();
        test::registry::on_destructor_error();
        cassert(registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::registry();
        test::registry::on_constructor_error();
        cassert(registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::registry();
        test::registry::on_operator_error();
        cassert(registry.empty());
        cassert(!registry.status());
    }
    {
        {
            auto registry = test::registry();
            test::registry::on_error("");
            test::registry::on_exception("");
            test::registry::on_destructor_error();
            test::registry::on_constructor_error();
            test::registry::on_operator_error();
        }
        cassert(test::return_value == test::exit_code::failure);
    }
}
