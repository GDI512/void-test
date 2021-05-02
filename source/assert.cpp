// ========================== assert.cpp ==========================
//
//  Part of the citrine library, under the BSD-3-Clause License.
//  See https://github.com/GDI512/citrine/blob/master/LICENSE for
//  license information.
//
// ================================================================

#include "assert.hpp"
#include "output.hpp"
#include "state.hpp"

namespace test {

    template <>
    auto handle<message::error>(string source) noexcept -> bool {
        report<message::error>();
        print<message::error>(source);
        return false;
    }

    template <>
    auto handle<message::success>(string source) noexcept -> bool {
        report<message::success>();
        print<message::success>(source);
        return true;
    }

}
