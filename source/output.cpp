#include <output.hpp>
#include <cstdio>

namespace test::core::format {

    constexpr auto space = "\040\040";
    constexpr auto ok = "(\033[32mok\033[0m\040%s)\n";
    constexpr auto unit = "(\033[93munit\033[0m\040%s)\n";
    constexpr auto error = "(\033[31merror\033[0m\040%s)\n";
    constexpr auto exception = "(\033[31munhandled\040exception\033[0m\040%s)\n";
    constexpr auto unit_error = "(\033[31munit\040error\033[0m\040[%i/%i])\n";
    constexpr auto unit_success = "(\033[32munit\040ok\033[0m\040[%i/%i])\n";
    constexpr auto resource_error = "(\033[31mresource\040error\033[0m\040[%i/%i]\040[%i/%i/%i])\n";
    constexpr auto resource_success = "(\033[32mresource\040ok\033[0m\040[%i/%i]\040[%i/%i/%i])\n";

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
        repeat(format::space, indent_level);
        printf(format::unit, name);
    }

    auto output::on_error(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::error, source);
    }

    auto output::on_success(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::ok, source);
    }

    auto output::on_exception(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::exception, source);
    }

    auto output::on_test_error(registry_state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::unit_error, data.error_count, data.success_count + data.error_count);
    }

    auto output::on_test_success(registry_state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::unit_success, data.error_count, data.success_count + data.error_count);
    }

    auto output::on_resource_error(verifier_state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::resource_error, data.destroyed_count, data.constructed_count, data.destructor_error_count,
               data.constructor_error_count, data.operator_error_count);
    }

    auto output::on_resource_success(verifier_state data) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::resource_success, data.destroyed_count, data.constructed_count, data.destructor_error_count,
               data.constructor_error_count, data.operator_error_count);
    }

}
