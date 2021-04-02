// ========================== object.cpp ==========================
//
//  Part of the cppltf library, under the BSD-3-Clause License.
//  See https://github.com/GDI512/cppltf/blob/master/LICENSE for
//  license information.
//
// ================================================================

#include <public/object.hpp>
#include <private/state.hpp>
#include <cstdint>

namespace test {

    constexpr auto invalid_pointer_value = static_cast<std::intptr_t>(0x7FFFFFFF);
    constexpr auto initialized_memory_value = static_cast<std::int32_t>(0x7FFFFFFF);
    constexpr auto uninitialized_memory_value = static_cast<std::int32_t>(0x00000000);

    object::~object() noexcept {
        report<message::destructor>();
        if (!is_initialized() || !is_self()) {
            report<message::destructor_error>();
        }
        self = reinterpret_cast<object*>(invalid_pointer_value);
        value = uninitialized_memory_value;
    }

    object::object(integer number) noexcept : self(this), number(number) {
        report<message::constructor>();
        if (is_initialized()) {
            report<message::constructor_error>();
        }
        value = initialized_memory_value;
    }

    object::object(object&& other) noexcept : self(this), number(other.number) {
        report<message::constructor>();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            report<message::constructor_error>();
        }
        value = initialized_memory_value;
    }

    object::object(const object& other) noexcept : self(this), number(other.number) {
        report<message::constructor>();
        if (is_initialized() || !other.is_self() || other.is_uninitialized()) {
            report<message::constructor_error>();
        }
        value = initialized_memory_value;
    }

    object::operator integer() const noexcept {
        return number;
    }

    auto object::operator=(object&& other) noexcept -> object& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            report<message::operator_error>();
        } else {
            number = other.number;
        }
        return *this;
    }

    auto object::operator=(const object& other) noexcept -> object& {
        if (!is_self() || !other.is_self() || is_uninitialized() || other.is_uninitialized()) {
            report<message::operator_error>();
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
        report<message::destructor>();
    }

    counter::counter(integer number) noexcept : number(number) {
        report<message::constructor>();
    }

    counter::counter(counter&& other) noexcept : number(other.number) {
        report<message::constructor>();
    }

    counter::counter(const counter& other) noexcept : number(other.number) {
        report<message::constructor>();
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
