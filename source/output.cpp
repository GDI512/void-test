#include <output.hpp>
#include <cstdio>

namespace void_test::core::format {

    constexpr auto space = "\040\040";
    constexpr auto scope = "(\033[93munit\033[0m\040%s)\n";
    constexpr auto error = "(\033[31merror\033[0m\040%s)\n";
    constexpr auto success = "(\033[32mok\033[0m\040%s)\n";
    constexpr auto exception = "(\033[31munhandled exception\033[0m\040%s)\n";
    constexpr auto registry_error = "(\033[31munit\040error\033[0m\040[%i/%i])\n";
    constexpr auto registry_success = "(\033[32munit\040ok\033[0m\040[%i/%i])\n";
    constexpr auto verifier_error = "(\033[31mverifier\040error\033[0m\040[%i/%i]\040[%i/%i/%i])\n";
    constexpr auto verifier_success = "(\033[32mverifier\040ok\033[0m\040[%i/%i]\040[%i/%i/%i])\n";

}

namespace void_test::core {

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
        repeat(format::space, indent_level);
        printf(format::scope, name);
    }

    auto output::on_error(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::error, source);
    }

    auto output::on_success(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::success, source);
    }

    auto output::on_exception(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::exception, source);
    }

    auto output::on_registry_error(registry::state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::registry_error, data.failed, data.passed + data.failed);
    }

    auto output::on_registry_success(registry::state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::registry_success, data.failed, data.passed + data.failed);
    }

    auto output::on_verifier_error(verifier::state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::verifier_error, data.destroyed, data.constructed, data.destructor_errors,
               data.constructor_errors, data.operator_errors);
    }

    auto output::on_verifier_success(verifier::state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::verifier_success, data.destroyed, data.constructed, data.destructor_errors,
               data.constructor_errors, data.operator_errors);
    }

}