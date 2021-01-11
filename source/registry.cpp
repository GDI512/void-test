#include <registry.hpp>
#include <output.hpp>
#include <state.hpp>

namespace void_test::core {

    registry::~registry() noexcept {
        if (status() && !empty()) {
            output::on_test_success(test);
        } else if (!status()) {
            exit_code = exit_failure;
            output::on_test_error(test);
        }
    }

    registry::registry() noexcept : test() {}

    auto registry::data() noexcept -> state {
        return current().test;
    }

    auto registry::empty() noexcept -> bool {
        return current().test.success_count == 0 && current().test.error_count == 0;
    }

    auto registry::status() noexcept -> bool {
        return current().test.error_count == 0;
    }

    auto registry::on_error(string source) noexcept -> size_type {
        output::on_error(source);
        return current().test.error_count++;
    }

    auto registry::on_success(string source) noexcept -> size_type {
        output::on_success(source);
        return current().test.success_count++;
    }

}
