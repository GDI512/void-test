#include <output.hpp>
#include <cstdio>

namespace test::core::fmt {

    constexpr auto space = "\040\040\040\040";
    constexpr auto scope = "(unit\040%s)\n";
    constexpr auto error = "(error\040%s)\n";
    constexpr auto success = "(ok\040%s)\n";
    constexpr auto exception = "(unhandled exception\040%s)\n";
    constexpr auto registry_error = "(unit\040-\040error\040[%i/%i])\n";
    constexpr auto registry_success = "(unit\040-\040ok\040[%i/%i])\n";
    constexpr auto verifier_error = "(verifier\040-\040error\040[%i/%i] [%i/%i/%i])\n";
    constexpr auto verifier_success = "(verifier\040-\040ok\040[%i/%i] [%i/%i/%i])\n";

}

namespace test::core {

    size_type output::indent_level = 0;

    output::~output() noexcept {
        indent_level--;
    }

    output::output() noexcept {
        indent_level++;
    }

    static auto repeat(string text, size_type count) noexcept -> void {
        while (count-- > 0) {
            fputs(text, stdout);
        }
    }

    auto output::on_scope(string name) noexcept -> void {
        repeat(fmt::space, indent_level);
        printf(fmt::scope, name);
    }

    auto output::on_error(string source) noexcept -> void {
        repeat(fmt::space, indent_level);
        printf(fmt::error, source);
    }

    auto output::on_success(string source) noexcept -> void {
        repeat(fmt::space, indent_level);
        printf(fmt::success, source);
    }

    auto output::on_exception(string source) noexcept -> void {
        repeat(fmt::space, indent_level);
        printf(fmt::exception, source);
    }

    auto output::on_test_registry_error(test_registry::state data) noexcept -> void {
        repeat(fmt::space, indent_level);
        printf(fmt::registry_error, data.failed, data.passed + data.failed);
    }

    auto output::on_test_registry_success(test_registry::state data) noexcept -> void {
        repeat(fmt::space, indent_level);
        printf(fmt::registry_success, data.failed, data.passed + data.failed);
    }

    auto output::on_resource_verifier_error(resource_verifier::state data) noexcept -> void {
        repeat(fmt::space, indent_level);
        printf(fmt::verifier_error, data.destroyed, data.constructed, data.destructor_errors, data.constructor_errors,
               data.operator_errors);
    }

    auto output::on_resource_verifier_success(resource_verifier::state data) noexcept -> void {
        repeat(fmt::space, indent_level);
        printf(fmt::verifier_success, data.destroyed, data.constructed, data.destructor_errors, data.constructor_errors,
               data.operator_errors);
    }

}