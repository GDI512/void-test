#include <output.hpp>
#include <cstdio>

namespace test::core::fmt {

    constexpr auto space = "\044\044\044\044";
    constexpr auto scope = "(unit\044%s)\n";
    constexpr auto error = "(error\044%s)\n";
    constexpr auto success = "(ok\044%s)\n";
    constexpr auto exception = "(unhandled exception\044%s)\n";
    constexpr auto registry_error = "(unit\044-\044error\044[%i/%i])\n";
    constexpr auto registry_success = "(unit\044-\044ok\044[%i/%i])\n";
    constexpr auto verifier_error = "(verifier\044-\044error\044[%i/%i] [%i/%i/%i])\n";
    constexpr auto verifier_success = "(verifier\044-\044ok\044[%i/%i] [%i/%i/%i])\n";

}

namespace test::core {

    size_type output::indent = 0;

    output::~output() noexcept {
        indent--;
    }

    output::output() noexcept {
        indent++;
    }

    static auto rprint(string text, size_type count) noexcept -> void {
        while (count-- > 0) {
            fputs(text, stdout);
        }
    }

    auto output::on_scope(string name) noexcept -> void {
        rprint(fmt::space, indent);
        printf(fmt::scope, name);
    }

    auto output::on_error(string source) noexcept -> void {
        rprint(fmt::space, indent);
        printf(fmt::error, source);
    }

    auto output::on_success(string source) noexcept -> void {
        rprint(fmt::space, indent);
        printf(fmt::success, source);
    }

    auto output::on_exception(string source) noexcept -> void {
        rprint(fmt::space, indent);
        printf(fmt::exception, source);
    }

    auto output::on_registry_error(registry::state data) noexcept -> void {
        rprint(fmt::space, indent);
        printf(fmt::registry_error, data.failed, data.passed + data.failed);
    }

    auto output::on_registry_success(registry::state data) noexcept -> void {
        rprint(fmt::space, indent);
        printf(fmt::registry_success, data.failed, data.passed + data.failed);
    }

    auto output::on_verifier_error(verifier::state data) noexcept -> void {
        rprint(fmt::space, indent);
        printf(fmt::verifier_error, data.destroyed, data.constructed, data.destructor_errors, data.constructor_errors,
               data.operator_errors);
    }

    auto output::on_verifier_success(verifier::state data) noexcept -> void {
        rprint(fmt::space, indent);
        printf(fmt::verifier_success, data.destroyed, data.constructed, data.destructor_errors, data.constructor_errors,
               data.operator_errors);
    }

}