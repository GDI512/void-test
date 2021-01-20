#include <type.hpp>
#include <state.hpp>
#include <cstdint>

namespace test {

    constexpr auto invalid_pointer_value = static_cast<intptr_t>(0x7FFFFFFF);
    constexpr auto initialized_memory_value = static_cast<int>(0x7FFFFFFF);
    constexpr auto uninitialized_memory_value = static_cast<int>(0x00000000);

    resource::~resource() noexcept {
        core::verifier::on_destruction();
        if (!is_initialized() || !is_self()) {
            core::verifier::on_destructor_error();
        }
        self = reinterpret_cast<resource*>(invalid_pointer_value);
        value = uninitialized_memory_value;
    }

    resource::resource() noexcept : self(this) {
        core::verifier::on_construction();
        if (is_initialized()) {
            core::verifier::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    resource::resource(resource&& other) noexcept : self(this) {
        core::verifier::on_construction();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            core::verifier::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    resource::resource(const resource& other) noexcept : self(this) {
        core::verifier::on_construction();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            core::verifier::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    auto resource::operator=(resource&& other) noexcept -> resource& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            core::verifier::on_operator_error();
        }
        return *this;
    }

    auto resource::operator=(const resource& other) noexcept -> resource& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            core::verifier::on_operator_error();
        }
        return *this;
    }

    auto resource::is_self() const noexcept -> bool {
        return self == this;
    }

    auto resource::is_initialized() const noexcept -> bool {
        return value == initialized_memory_value;
    }

    auto resource::is_uninitialized() const noexcept -> bool {
        return value == uninitialized_memory_value;
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
