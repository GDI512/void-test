#include <output.hpp>
#include <state.hpp>
#include <cstdarg>
#include <cstdio>

namespace {

    using namespace test;

    auto indent() noexcept {
        ++core::output::level;
    }

    auto outdent() noexcept {
        --core::output::level;
    }

    auto repeat(string text, size_type count) noexcept {
        while (count-- > 0)
            std::fputs(text, stdout);
    }

    auto print(string format, ...) noexcept {
        va_list args;
        va_start(args, format);
        std::vprintf(format, args);
        va_end(args);
    }

}

namespace test::format {

    constexpr auto space = "\040\040";
    constexpr auto scope = "(\033[93munit\033[0m %s)\n";
    constexpr auto error = "(\033[31merror\033[0m %s)\n";
    constexpr auto success = "(\033[32mok\033[0m %s)\n";
    constexpr auto exception = "(\033[31mexception\033[0m\040%s)\n";
    constexpr auto test_error = "(\033[31mtest\040error\033[0m\040[%zu/%zu])\n";
    constexpr auto test_success = "(\033[32mtest\040ok\033[0m\040[%zu/%zu])\n";
    constexpr auto resource_error = "(\033[31mresource\040error\033[0m\040[%zu/%zu]\040[%zu/%zu/%zu])\n";
    constexpr auto resource_success = "(\033[32mresource\040ok\033[0m\040[%zu/%zu]\040[%zu/%zu/%zu])\n";

}

namespace test::core {

    size_type output::level = 0;

    output::~output() noexcept {
        ::outdent();
    }

    output::output(string name) noexcept {
        ::repeat(format::space, level);
        ::print(format::scope, name);
        ::indent();
    }

    auto output::on_error(string source) noexcept -> void {
        ::repeat(format::space, level);
        ::print(format::error, source);
    }

    auto output::on_success(string source) noexcept -> void {
        ::repeat(format::space, level);
        ::print(format::success, source);
    }

    auto output::on_exception(string source) noexcept -> void {
        ::repeat(format::space, level);
        ::print(format::exception, source);
    }

    auto output::on_unit_error(state_array result) noexcept -> void {
        if (result[state::checks] != 0) {
            ::repeat(format::space, level);
            ::print(format::test_error, result[state::errors], result[state::checks]);
        }
        if (result[state::destructors] + result[state::constructors] != 0) {
            ::repeat(format::space, level);
            ::print(format::resource_error, result[state::destructors], result[state::constructors],
                result[state::destructor_errors], result[state::constructor_errors], result[state::assignment_errors]);
        }
    }

    auto output::on_unit_success(state_array result) noexcept -> void {
        if (result[state::checks] != 0) {
            ::repeat(format::space, level);
            ::print(format::test_success, result[state::errors], result[state::checks]);
        }
        if (result[state::destructors] + result[state::constructors] != 0) {
            ::repeat(format::space, level);
            ::print(format::resource_success, result[state::destructors], result[state::constructors],
                result[state::destructor_errors], result[state::constructor_errors], result[state::assignment_errors]);
        }
    }

}
