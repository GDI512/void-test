#include "common.hpp"

#include <new>
#include <utility>

using namespace test;

int main() {
    {
        auto tracker = core::verifier();
        auto object = resource();
        cassert(core::global_resource_state.destroyed_count == 0);
        cassert(core::global_resource_state.constructed_count == 1);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        object.~resource();
        cassert(core::global_resource_state.destroyed_count == 1);
        cassert(core::global_resource_state.constructed_count == 1);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        object.~resource();
        object.~resource();
        cassert(core::global_resource_state.destroyed_count == 2);
        cassert(core::global_resource_state.constructed_count == 1);
        cassert(core::global_resource_state.destructor_error_count == 1);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        new (&object) resource();
        cassert(core::global_resource_state.destroyed_count == 0);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 1);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        auto other = resource(object);
        cassert(core::global_resource_state.destroyed_count == 0);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        auto other = resource(std::move(object));
        cassert(core::global_resource_state.destroyed_count == 0);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        object.~resource();
        auto other = resource(object);
        cassert(core::global_resource_state.destroyed_count == 1);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 1);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        object.~resource();
        auto other = resource(std::move(object));
        cassert(core::global_resource_state.destroyed_count == 1);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 1);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        auto other = resource();
        object = other;
        cassert(core::global_resource_state.destroyed_count == 0);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        auto other = resource();
        object = std::move(other);
        cassert(core::global_resource_state.destroyed_count == 0);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 0);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        auto other = resource();
        object.~resource();
        object = other;
        cassert(core::global_resource_state.destroyed_count == 1);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        auto other = resource();
        object.~resource();
        object = std::move(other);
        cassert(core::global_resource_state.destroyed_count == 1);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        auto other = resource();
        other.~resource();
        object = other;
        cassert(core::global_resource_state.destroyed_count == 1);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 1);
    }
    {
        auto tracker = core::verifier();
        auto object = resource();
        auto other = resource();
        other.~resource();
        object = std::move(other);
        cassert(core::global_resource_state.destroyed_count == 1);
        cassert(core::global_resource_state.constructed_count == 2);
        cassert(core::global_resource_state.destructor_error_count == 0);
        cassert(core::global_resource_state.constructor_error_count == 0);
        cassert(core::global_resource_state.operator_error_count == 1);
    }
    //
}
