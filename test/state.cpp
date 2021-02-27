#include "common.hpp"

int main() {
    {
        cassert(test::aux::exit_value == test::aux::exit_code::success);
    }
    {
        auto registry = test::aux::registry{};
        cassert(registry.empty());
        cassert(registry.status());
    }
    {
        auto registry = test::aux::registry{};
        test::aux::registry::on_error("");
        cassert(!registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::aux::registry{};
        test::aux::registry::on_success("");
        cassert(!registry.empty());
        cassert(registry.status());
    }
    {
        auto registry = test::aux::registry{};
        test::aux::registry::on_exception("");
        cassert(!registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::aux::registry{};
        test::aux::registry::on_destruction();
        cassert(!registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::aux::registry{};
        test::aux::registry::on_destruction();
        test::aux::registry::on_construction();
        cassert(!registry.empty());
        cassert(registry.status());
    }
    {
        auto registry = test::aux::registry{};
        test::aux::registry::on_destructor_error();
        cassert(registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::aux::registry{};
        test::aux::registry::on_constructor_error();
        cassert(registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::aux::registry{};
        test::aux::registry::on_operator_error();
        cassert(registry.empty());
        cassert(!registry.status());
    }
    {
        {
            auto registry = test::aux::registry{};
            test::aux::registry::on_error("");
            test::aux::registry::on_exception("");
            test::aux::registry::on_destructor_error();
            test::aux::registry::on_constructor_error();
            test::aux::registry::on_operator_error();
        }
        cassert(test::aux::exit_value == test::aux::exit_code::failure);
    }
}
