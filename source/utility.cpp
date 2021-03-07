#include <utility.hpp>
#include <output.hpp>
#include <state.hpp>

namespace test::core {

    auto on_error(string source) noexcept -> bool {
        core::registry::on_error();
        core::output::on_error(source);
        return false;
    }

    auto on_success(string source) noexcept -> bool {
        core::registry::on_success();
        core::output::on_success(source);
        return true;
    }

    auto on_exception(string source) noexcept -> void {
        core::registry::on_exception();
        core::output::on_exception(source);
    }

}
