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

    auto registry::data() const noexcept -> state {
        return count;
    }

    auto registry::empty() const noexcept -> bool {
        return count.passed == 0 && count.failed == 0;
    }

    auto registry::status() const noexcept -> bool {
        return count.failed == 0;
    }

    auto registry::on_error() noexcept -> size_type {
        return count.failed++;
    }

    auto registry::on_success() noexcept -> size_type {
        return count.passed++;
    }

}
