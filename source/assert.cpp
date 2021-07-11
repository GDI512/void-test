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
