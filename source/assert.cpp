#include <assert.hpp>

namespace test {

    template <>
    auto action<message::error>(string source) noexcept -> bool {
        report<message::error>();
        print<message::error>(source);
        return false;
    }

    template <>
    auto action<message::success>(string source) noexcept -> bool {
        report<message::success>();
        print<message::success>(source);
        return true;
    }

    template <>
    auto action<message::exception>(string source) noexcept -> bool {
        static_cast<void>(source);
        report<message::exception>();
        print<message::exception>();
        return false;
    }

}
