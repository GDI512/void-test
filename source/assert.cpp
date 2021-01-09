#include <assert.hpp>

namespace void_test::core {

    auto on_success(string source) noexcept -> bool {
        core::registry::on_success();
        core::output::on_success(source);
        return true;
    }

    auto on_error(string source) noexcept -> bool {
        core::registry::on_error();
        core::output::on_error(source);
        return false;
    }

}

namespace void_test {

    auto check(bool value) noexcept -> bool {
        if (value) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

}
