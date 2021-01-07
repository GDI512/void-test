#include <registry.hpp>
#include <output.hpp>
#include <state.hpp>

namespace void_test::core {

    registry::~registry() noexcept {
        if (status() && !empty()) {
            output::on_registry_success(count);
        } else if (!status()) {
            exit_status = exit_failure;
            output::on_registry_error(count);
        }
    }

    registry::registry() noexcept : count() {}

    auto registry::data() noexcept -> state {
        return current().count;
    }

    auto registry::empty() noexcept -> bool {
        return current().count.passed == 0 && current().count.failed == 0;
    }

    auto registry::status() noexcept -> bool {
        return current().count.failed == 0;
    }

    auto registry::on_error() noexcept -> size_type {
        return current().count.failed++;
    }

    auto registry::on_success() noexcept -> size_type {
        return current().count.passed++;
    }

}
