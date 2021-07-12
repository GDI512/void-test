#include "state.hpp"
#include "type.hpp"

#include <cstdint>

namespace test {

    counter::~counter() noexcept {
        unit_state::active().on_destruction();
    }

    counter::counter(int value) noexcept : value(value) {
        unit_state::active().on_construction();
    }

    counter::counter(counter&& other) noexcept : value(other.value) {
        unit_state::active().on_construction();
    }

    counter::counter(const counter& other) noexcept : value(other.value) {
        unit_state::active().on_construction();
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
