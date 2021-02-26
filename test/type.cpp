#include "common.hpp"

#include <utility>
#include <new>

using namespace test;

int main() {
    {
        auto tracker = core::verifier();
        const auto instance = object(16);
        auto other = object(32);
        CASSERT(instance == 16);
        CASSERT(other == 32);
        other = instance;
        CASSERT(instance == 16);
        CASSERT(other == 16);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        CASSERT(core::global.object_state.destroyed_count == 0);
        CASSERT(core::global.object_state.constructed_count == 1);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        CASSERT(core::global.object_state.destroyed_count == 1);
        CASSERT(core::global.object_state.constructed_count == 1);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        instance.~object();
        CASSERT(core::global.object_state.destroyed_count == 2);
        CASSERT(core::global.object_state.constructed_count == 1);
        CASSERT(core::global.object_state.destructor_error_count == 1);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        new (&instance) object();
        CASSERT(core::global.object_state.destroyed_count == 0);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 1);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object(instance);
        CASSERT(core::global.object_state.destroyed_count == 0);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object(std::move(instance));
        CASSERT(core::global.object_state.destroyed_count == 0);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        auto other = object(instance);
        CASSERT(core::global.object_state.destroyed_count == 1);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 1);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        auto other = object(std::move(instance));
        CASSERT(core::global.object_state.destroyed_count == 1);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 1);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance = other;
        CASSERT(core::global.object_state.destroyed_count == 0);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance = std::move(other);
        CASSERT(core::global.object_state.destroyed_count == 0);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance.~object();
        instance = other;
        CASSERT(core::global.object_state.destroyed_count == 1);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance.~object();
        instance = std::move(other);
        CASSERT(core::global.object_state.destroyed_count == 1);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        other.~object();
        instance = other;
        CASSERT(core::global.object_state.destroyed_count == 1);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        other.~object();
        instance = std::move(other);
        CASSERT(core::global.object_state.destroyed_count == 1);
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destructor_error_count == 0);
        CASSERT(core::global.object_state.constructor_error_count == 0);
        CASSERT(core::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = counter();
        CASSERT(core::global.object_state.constructed_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = counter();
        auto other = counter(instance);
        CASSERT(core::global.object_state.constructed_count == 2);
    }
    {
        auto tracker = core::verifier();
        auto instance = counter();
        auto other = counter(std::move(instance));
        CASSERT(core::global.object_state.constructed_count == 2);
    }
    {
        auto tracker = core::verifier();
        {
            auto instance = counter();
            auto other = counter();
        }
        CASSERT(core::global.object_state.constructed_count == 2);
        CASSERT(core::global.object_state.destroyed_count == 2);
    }
}
