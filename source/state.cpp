#include <state.hpp>
#include <output.hpp>

namespace void_test {

    auto exit_status() noexcept -> int {
        return core::exit_status;
    }

}

namespace void_test::core {

    int exit_status = exit_success;

}
