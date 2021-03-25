#include "common.hpp"

#include <state.hpp>

int main() {
    {
        const auto context = test::registry("");
        test::on_error("");
        cassert(!context.ok());
        cassert(!context.empty());
    }
    {
        const auto context = test::registry("");
        test::on_success("");
        cassert(context.ok());
        cassert(!context.empty());
    }
    {
        const auto context = test::registry("");
        test::on_exception();
        cassert(!context.ok());
        cassert(!context.empty());
    }
    {
        const auto context = test::registry("");
        test::on_destructor();
        cassert(!context.ok());
        cassert(!context.empty());
    }
    {
        const auto context = test::registry("");
        test::on_constructor();
        cassert(!context.ok());
        cassert(!context.empty());
    }
    {
        const auto context = test::registry("");
        test::on_destructor();
        test::on_constructor();
        cassert(context.ok());
        cassert(!context.empty());
    }
    {
        const auto context = test::registry("");
        test::on_destructor_error();
        cassert(!context.ok());
        cassert(!context.empty());
    }
    {
        const auto context = test::registry("");
        test::on_constructor_error();
        cassert(!context.ok());
        cassert(!context.empty());
    }
    {
        const auto context = test::registry("");
        test::on_operator_error();
        cassert(!context.ok());
        cassert(!context.empty());
    }
}
