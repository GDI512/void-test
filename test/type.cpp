#include "common.hpp"

#include <utility>
#include <new>

using namespace test;

int main() {
    {
        auto tracker = core::verifier();
        const auto instance = object(16);
        auto other = object(32);
        cassert(instance == 16);
        cassert(other == 32);
        other = instance;
        cassert(instance == 16);
        cassert(other == 16);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        cassert(core::global.object_state.destroyed_count == 0);
        cassert(core::global.object_state.constructed_count == 1);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        cassert(core::global.object_state.destroyed_count == 1);
        cassert(core::global.object_state.constructed_count == 1);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        instance.~object();
        cassert(core::global.object_state.destroyed_count == 2);
        cassert(core::global.object_state.constructed_count == 1);
        cassert(core::global.object_state.destructor_error_count == 1);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        new (&instance) object();
        cassert(core::global.object_state.destroyed_count == 0);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 1);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object(instance);
        cassert(core::global.object_state.destroyed_count == 0);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object(std::move(instance));
        cassert(core::global.object_state.destroyed_count == 0);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        auto other = object(instance);
        cassert(core::global.object_state.destroyed_count == 1);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 1);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        auto other = object(std::move(instance));
        cassert(core::global.object_state.destroyed_count == 1);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 1);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance = other;
        cassert(core::global.object_state.destroyed_count == 0);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance = std::move(other);
        cassert(core::global.object_state.destroyed_count == 0);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance.~object();
        instance = other;
        cassert(core::global.object_state.destroyed_count == 1);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance.~object();
        instance = std::move(other);
        cassert(core::global.object_state.destroyed_count == 1);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        other.~object();
        instance = other;
        cassert(core::global.object_state.destroyed_count == 1);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        other.~object();
        instance = std::move(other);
        cassert(core::global.object_state.destroyed_count == 1);
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destructor_error_count == 0);
        cassert(core::global.object_state.constructor_error_count == 0);
        cassert(core::global.object_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = counter();
        cassert(core::global.object_state.constructed_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = counter();
        auto other = counter(instance);
        cassert(core::global.object_state.constructed_count == 2);
    }
    {
        auto tracker = core::verifier();
        auto instance = counter();
        auto other = counter(std::move(instance));
        cassert(core::global.object_state.constructed_count == 2);
    }
    {
        auto tracker = core::verifier();
        {
            auto instance = counter();
            auto other = counter();
        }
        cassert(core::global.object_state.constructed_count == 2);
        cassert(core::global.object_state.destroyed_count == 2);
    }
}
