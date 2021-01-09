#include <assert.hpp>

namespace void_test {

    auto check(bool value) noexcept -> bool {
        if (value) {
            return core::on_success(__func__);
        } else {
            return core::on_error(__func__);
        }
    }

}
