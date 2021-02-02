#include "common.hpp"

#include <new>
#include <utility>

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
        cassert(core::global.object.destroyed_count == 0);
        cassert(core::global.object.constructed_count == 1);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        cassert(core::global.object.destroyed_count == 1);
        cassert(core::global.object.constructed_count == 1);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        instance.~object();
        cassert(core::global.object.destroyed_count == 2);
        cassert(core::global.object.constructed_count == 1);
        cassert(core::global.object.destructor_error_count == 1);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        new (&instance) object();
        cassert(core::global.object.destroyed_count == 0);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 1);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object(instance);
        cassert(core::global.object.destroyed_count == 0);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object(std::move(instance));
        cassert(core::global.object.destroyed_count == 0);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        auto other = object(instance);
        cassert(core::global.object.destroyed_count == 1);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 1);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        instance.~object();
        auto other = object(std::move(instance));
        cassert(core::global.object.destroyed_count == 1);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 1);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance = other;
        cassert(core::global.object.destroyed_count == 0);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance = std::move(other);
        cassert(core::global.object.destroyed_count == 0);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance.~object();
        instance = other;
        cassert(core::global.object.destroyed_count == 1);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        instance.~object();
        instance = std::move(other);
        cassert(core::global.object.destroyed_count == 1);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        other.~object();
        instance = other;
        cassert(core::global.object.destroyed_count == 1);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto instance = object();
        auto other = object();
        other.~object();
        instance = std::move(other);
        cassert(core::global.object.destroyed_count == 1);
        cassert(core::global.object.constructed_count == 2);
        cassert(core::global.object.destructor_error_count == 0);
        cassert(core::global.object.constructor_error_count == 0);
        cassert(core::global.object.operator_error_count == 1);
    }
}
