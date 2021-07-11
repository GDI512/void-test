#include "state.hpp"
#include "type.hpp"

#include <cstdint>

namespace test {

    counter::~counter() noexcept {
        report<message::destructor>();
    }

    counter::counter(int value) noexcept : value(value) {
        report<message::constructor>();
    }

    counter::counter(counter&& other) noexcept : value(other.value) {
        report<message::constructor>();
    }

    counter::counter(const counter& other) noexcept : value(other.value) {
        report<message::constructor>();
    }

    counter::operator int() const noexcept {
        return value;
    }

    auto counter::operator=(counter&& other) noexcept -> counter& {
        value = other.value;
        return *this;
    }

    auto counter::operator=(const counter& other) noexcept -> counter& {
        value = other.value;
        return *this;
    }

}
