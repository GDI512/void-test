#include <type.hpp>
#include <state.hpp>
#include <cstdint>

namespace test {

    constexpr auto invalid_pointer_value = static_cast<intptr_t>(0x7FFFFFFF);
    constexpr auto initialized_memory_value = static_cast<int>(0x7FFFFFFF);
    constexpr auto uninitialized_memory_value = static_cast<int>(0x00000000);

    object::~object() noexcept {
        registry::on_destruction();
        if (!is_initialized() || !is_self()) {
            registry::on_destructor_error();
        }
        self = reinterpret_cast<object*>(invalid_pointer_value);
        value = uninitialized_memory_value;
    }

    object::object(int number) noexcept : number(number), self(this) {
        registry::on_construction();
        if (is_initialized()) {
            registry::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    object::object(object&& other) noexcept : number(other.number), self(this) {
        registry::on_construction();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            registry::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    object::object(const object& other) noexcept : number(other.number), self(this) {
        registry::on_construction();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            registry::on_constructor_error();
        }
        value = initialized_memory_value;
    }

    object::operator int() const noexcept {
        return number;
    }

    auto object::operator=(object&& other) noexcept -> object& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            registry::on_operator_error();
        } else {
            number = other.number;
        }
        return *this;
    }

    auto object::operator=(const object& other) noexcept -> object& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            registry::on_operator_error();
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
        registry::on_destruction();
    }

    counter::counter() noexcept {
        registry::on_construction();
    }

    counter::counter(counter&& other) noexcept {
        static_cast<void>(other);
        registry::on_construction();
    }

    counter::counter(const counter& other) noexcept {
        static_cast<void>(other);
        registry::on_construction();
    }

    auto counter::operator=(counter&& other) noexcept -> counter& {
        static_cast<void>(other);
        return *this;
    }

    auto counter::operator=(const counter& other) noexcept -> counter& {
        static_cast<void>(other);
        return *this;
    }

    auto operator==(const counter& left, const counter& right) noexcept -> bool {
        static_cast<void>(left);
        static_cast<void>(right);
        return true;
    }

    auto operator!=(const counter& left, const counter& right) noexcept -> bool {
        static_cast<void>(left);
        static_cast<void>(right);
        return false;
    }

}
