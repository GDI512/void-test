#include <resource.hpp>
#include <verifier.hpp>
#include <cstdint>

namespace void_test {

    constexpr auto invalid_pointer_value = static_cast<intptr_t>(0xBEEF);
    constexpr auto initialized_memory_value = static_cast<int>(0xFFFF);
    constexpr auto uninitialized_memory_value = static_cast<int>(0x0000);

    resource::~resource() noexcept {
        core::verifier::current().on_destruction();
        if (self != this) {
            core::verifier::current().on_destructor_error();
        }
        self = reinterpret_cast<resource*>(invalid_pointer_value);
        value = uninitialized_memory_value;
    }

    resource::resource() noexcept : self(this) {
        core::verifier::current().on_construction();
        if (value == initialized_memory_value) {
            core::verifier::current().on_constructor_error();
        }
        value = initialized_memory_value;
    }

    resource::resource(resource&& other) noexcept : self(this) {
        core::verifier::current().on_construction();
        if (other.self != &other || value == initialized_memory_value) {
            core::verifier::current().on_constructor_error();
        }
        value = initialized_memory_value;
    }

    resource::resource(const resource& other) noexcept : self(this) {
        core::verifier::current().on_construction();
        if (other.self != &other || value == initialized_memory_value) {
            core::verifier::current().on_constructor_error();
        }
        value = initialized_memory_value;
    }

    auto resource::operator=(resource&& other) noexcept -> resource& {
        if (self != this || other.self != &other) {
            core::verifier::current().on_operator_error();
        }
        return *this;
    }

    auto resource::operator=(const resource& other) noexcept -> resource& {
        if (self != this || other.self != &other) {
            core::verifier::current().on_operator_error();
        }
        return *this;
    }

}
