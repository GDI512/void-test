#include "common.hpp"

int main() {
    {
        cassert(test::core::code == test::core::exit_code::success);
    }
    {
        auto registry = test::core::registry{};
        cassert(registry.empty());
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        test::core::registry::on_error();
        cassert(!registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        test::core::registry::on_success();
        cassert(!registry.empty());
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        test::core::registry::on_exception();
        cassert(!registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        test::core::registry::on_destruction();
        cassert(!registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        test::core::registry::on_destruction();
        test::core::registry::on_construction();
        cassert(!registry.empty());
        cassert(registry.status());
    }
    {
        auto registry = test::core::registry{};
        test::core::registry::on_destructor_error();
        cassert(registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        test::core::registry::on_constructor_error();
        cassert(registry.empty());
        cassert(!registry.status());
    }
    {
        auto registry = test::core::registry{};
        test::core::registry::on_operator_error();
        cassert(registry.empty());
        cassert(!registry.status());
    }
    {
        {
            auto registry = test::core::registry{};
            test::core::registry::on_error();
            test::core::registry::on_exception();
            test::core::registry::on_destructor_error();
            test::core::registry::on_constructor_error();
            test::core::registry::on_operator_error();
        }
        cassert(test::core::code == test::core::exit_code::failure);
    }
}
