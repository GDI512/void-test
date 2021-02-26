#include "common.hpp"

#include <utility>
#include <new>

int main() {
    {
        auto tracker = test::verifier();
        const auto instance = test::object(16);
        auto other = test::object(32);
        CASSERT(instance == 16);
        CASSERT(other == 32);
        other = instance;
        CASSERT(instance == 16);
        CASSERT(other == 16);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        CASSERT(test::global.object_state.destroyed_count == 0);
        CASSERT(test::global.object_state.constructed_count == 1);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        instance.~object();
        CASSERT(test::global.object_state.destroyed_count == 1);
        CASSERT(test::global.object_state.constructed_count == 1);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        instance.~object();
        instance.~object();
        CASSERT(test::global.object_state.destroyed_count == 2);
        CASSERT(test::global.object_state.constructed_count == 1);
        CASSERT(test::global.object_state.destructor_error_count == 1);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        new (&instance) test::object();
        CASSERT(test::global.object_state.destroyed_count == 0);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 1);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        auto other = test::object(instance);
        CASSERT(test::global.object_state.destroyed_count == 0);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        auto other = test::object(std::move(instance));
        CASSERT(test::global.object_state.destroyed_count == 0);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        instance.~object();
        auto other = test::object(instance);
        CASSERT(test::global.object_state.destroyed_count == 1);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 1);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        instance.~object();
        auto other = test::object(std::move(instance));
        CASSERT(test::global.object_state.destroyed_count == 1);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 1);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        auto other = test::object();
        instance = other;
        CASSERT(test::global.object_state.destroyed_count == 0);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        auto other = test::object();
        instance = std::move(other);
        CASSERT(test::global.object_state.destroyed_count == 0);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        auto other = test::object();
        instance.~object();
        instance = other;
        CASSERT(test::global.object_state.destroyed_count == 1);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        auto other = test::object();
        instance.~object();
        instance = std::move(other);
        CASSERT(test::global.object_state.destroyed_count == 1);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        auto other = test::object();
        other.~object();
        instance = other;
        CASSERT(test::global.object_state.destroyed_count == 1);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::object();
        auto other = test::object();
        other.~object();
        instance = std::move(other);
        CASSERT(test::global.object_state.destroyed_count == 1);
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destructor_error_count == 0);
        CASSERT(test::global.object_state.constructor_error_count == 0);
        CASSERT(test::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::counter();
        CASSERT(test::global.object_state.constructed_count == 1);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::counter();
        auto other = test::counter(instance);
        CASSERT(test::global.object_state.constructed_count == 2);
    }
    {
        auto tracker = test::verifier();
        auto instance = test::counter();
        auto other = test::counter(std::move(instance));
        CASSERT(test::global.object_state.constructed_count == 2);
    }
    {
        auto tracker = test::verifier();
        {
            auto instance = test::counter();
            auto other = test::counter();
        }
        CASSERT(test::global.object_state.constructed_count == 2);
        CASSERT(test::global.object_state.destroyed_count == 2);
    }
}
