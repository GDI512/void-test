#include <type.hpp>
#include <state.hpp>
#include <cstdint>

namespace test {

    constexpr auto invalid_pointer_value = static_cast<intptr_t>(0x7FFFFFFF);
    constexpr auto initialized_memory_value = static_cast<int>(0x7FFFFFFF);
    constexpr auto uninitialized_memory_value = static_cast<int>(0x00000000);

    object::~object() noexcept {
        core::on_destruction();
        if (!is_initialized() || !is_self()) {
            core::on_destructor_error();
        }
        self = reinterpret_cast<object*>(invalid_pointer_value);
        value = uninitialized_memory_value;
    }

    object::object() noexcept : self(this) {
        core::on_construction();
        if (is_initialized()) {
            core::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    object::object(object&& other) noexcept : self(this) {
        core::on_construction();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            core::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    object::object(const object& other) noexcept : self(this) {
        core::on_construction();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            core::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    auto object::operator=(object&& other) noexcept -> object& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            core::on_operator_error();
        }
        return *this;
    }

    auto object::operator=(const object& other) noexcept -> object& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            core::on_operator_error();
        }
        return *this;
    }

    auto object::is_self() const noexcept -> bool {
        return self == this;
    }

    auto object::is_initialized() const noexcept -> bool {
        return value == initialized_memory_value;
    }

    auto object::is_uninitialized() const noexcept -> bool {
        return value == uninitialized_memory_value;
    }

    auto operator==(const object& left, const object& right) noexcept -> bool {
        static_cast<void>(left);
        static_cast<void>(right);
        return true;
    }

    auto operator!=(const object& left, const object& right) noexcept -> bool {
        static_cast<void>(left);
        static_cast<void>(right);
        return false;
    }

}
