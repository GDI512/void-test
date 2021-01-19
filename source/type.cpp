#include <type.hpp>
#include <state.hpp>
#include <cstdint>

namespace void_test {

    constexpr auto invalid_pointer_value = static_cast<intptr_t>(0x7FFFFFFF);
    constexpr auto initialized_memory_value = static_cast<int>(0x7FFFFFFF);
    constexpr auto uninitialized_memory_value = static_cast<int>(0x00000000);

    resource::~resource() noexcept {
        core::verifier::on_destruction();
        if (value != initialized_memory_value || self != this) {
            core::verifier::on_destructor_error();
        }
        self = reinterpret_cast<resource*>(invalid_pointer_value);
        value = uninitialized_memory_value;
    }

    resource::resource() noexcept : self(this) {
        core::verifier::on_construction();
        if (value == initialized_memory_value) {
            core::verifier::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    resource::resource(resource&& other) noexcept : self(this) {
        core::verifier::on_construction();
        if (other.self != &other || value == initialized_memory_value) {
            core::verifier::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    resource::resource(const resource& other) noexcept : self(this) {
        core::verifier::on_construction();
        if (other.self != &other || value == initialized_memory_value) {
            core::verifier::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    auto resource::operator=(resource&& other) noexcept -> resource& {
        if (self != this || other.self != &other) {
            core::verifier::on_operator_error();
        }
        return *this;
    }

    auto resource::operator=(const resource& other) noexcept -> resource& {
        if (self != this || other.self != &other) {
            core::verifier::on_operator_error();
        }
        return *this;
    }

    auto operator==(const resource& left, const resource& right) noexcept -> bool {
        static_cast<void>(left);
        static_cast<void>(right);
        return true;
    }

    auto operator!=(const resource& left, const resource& right) noexcept -> bool {
        static_cast<void>(left);
        static_cast<void>(right);
        return false;
    }

}
