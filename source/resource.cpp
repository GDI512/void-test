#include <resource.hpp>
#include <state.hpp>

namespace test {

    constexpr auto invalid_pointer_value = 0xBEEF;

    resource::~resource() noexcept {
        core::verifier::on_destruction();
        if (self != this) {
            core::verifier::on_destructor_error();
        }
        self = reinterpret_cast<resource*>(invalid_pointer_value);
    }

    resource::resource(int value) noexcept : value(value), self(this) {
        core::verifier::on_contruction();
    }

    resource::resource(resource&& other) noexcept : value(other.value), self(this) {
        core::verifier::on_contruction();
        if (other.self != &other) {
            core::verifier::on_constructor_error();
        }
    }

    resource::resource(const resource& other) noexcept : value(other.value), self(this) {
        core::verifier::on_contruction();
        if (other.self != &other) {
            core::verifier::on_constructor_error();
        }
    }

    resource::operator int() const noexcept {
        return value;
    }

    resource::operator int&() noexcept {
        return value;
    }

    auto resource::operator=(resource&& other) noexcept -> resource& {
        value = other.value;
        if (self != this || other.self != &other) {
            core::verifier::on_operator_error();
        }
        return *this;
    }

    auto resource::operator=(const resource& other) noexcept -> resource& {
        value = other.value;
        if (self != this || other.self != &other) {
            core::verifier::on_operator_error();
        }
        return *this;
    }

}
