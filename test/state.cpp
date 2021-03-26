#include "common.hpp"

#include <state.hpp>

int main() {
    {
        const auto context = test::registry("");
        test::report<test::message::error>();
        cassert(!context.empty());
        cassert(!context.status());
    }
    {
        const auto context = test::registry("");
        test::report<test::message::success>();
        cassert(!context.empty());
        cassert(context.status());
    }
    {
        const auto context = test::registry("");
        test::report<test::message::exception>();
        cassert(!context.empty());
        cassert(!context.status());
    }
    {
        const auto context = test::registry("");
        test::report<test::message::destructor>();
        cassert(!context.empty());
        cassert(!context.status());
    }
    {
        const auto context = test::registry("");
        test::report<test::message::constructor>();
        cassert(!context.empty());
        cassert(!context.status());
    }
    {
        const auto context = test::registry("");
        test::report<test::message::destructor>();
        test::report<test::message::constructor>();
        cassert(!context.empty());
        cassert(context.status());
    }
    {
        const auto context = test::registry("");
        test::report<test::message::destructor_error>();
        cassert(!context.empty());
        cassert(!context.status());
    }
    {
        const auto context = test::registry("");
        test::report<test::message::constructor_error>();
        cassert(!context.empty());
        cassert(!context.status());
    }
    {
        const auto context = test::registry("");
        test::report<test::message::operator_error>();
        cassert(!context.empty());
        cassert(!context.status());
    }
}
