#include <object.hpp>
#include <state.hpp>
#include <cstdint>

namespace test {

    constexpr auto invalid_pointer_value = static_cast<std::intptr_t>(0x7FFFFFFF);
    constexpr auto initialized_memory_value = static_cast<std::int32_t>(0x7FFFFFFF);
    constexpr auto uninitialized_memory_value = static_cast<std::int32_t>(0x00000000);

    object::~object() noexcept {
        on_destructor();
        if (!is_initialized() || !is_self()) {
            on_destructor_error();
        }
        self = reinterpret_cast<object*>(invalid_pointer_value);
        value = uninitialized_memory_value;
    }

    object::object(integer number) noexcept : self(this), number(number) {
        on_constructor();
        if (is_initialized()) {
            on_constructor_error();
        }
        value = initialized_memory_value;
    }

    object::object(object&& other) noexcept : self(this), number(other.number) {
        on_constructor();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            on_constructor_error();
        }
        value = initialized_memory_value;
    }

    object::object(const object& other) noexcept : self(this), number(other.number) {
        on_constructor();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            on_constructor_error();
        }
        value = initialized_memory_value;
    }

    object::operator integer() const noexcept {
        return number;
    }

    auto object::operator=(object&& other) noexcept -> object& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            on_operator_error();
        } else {
            number = other.number;
        }
        return *this;
    }

    auto object::operator=(const object& other) noexcept -> object& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            on_operator_error();
        } else {
            number = other.number;
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

    counter::~counter() noexcept {
        on_destructor();
    }

    counter::counter(integer number) noexcept : number(number) {
        on_constructor();
    }

    counter::counter(counter&& other) noexcept : number(other.number) {
        on_constructor();
    }

    counter::counter(const counter& other) noexcept : number(other.number) {
        on_constructor();
    }

    counter::operator integer() const noexcept {
        return number;
    }

    auto counter::operator=(counter&& other) noexcept -> counter& {
        number = other.number;
        return *this;
    }

    auto counter::operator=(const counter& other) noexcept -> counter& {
        number = other.number;
        return *this;
    }

}
