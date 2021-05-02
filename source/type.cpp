// =========================== type.cpp ===========================
//
//  Part of the citrine library, under the BSD-3-Clause License.
//  See https://github.com/GDI512/citrine/blob/master/LICENSE for
//  license information.
//
// ================================================================

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
