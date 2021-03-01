#include <output.hpp>
#include <state.hpp>
#include <cstdarg>
#include <cstdio>

namespace {

    using namespace test;

    auto indent() noexcept {
        ++core::output::indentation;
    }

    auto outdent() noexcept {
        --core::output::indentation;
    }

    auto repeat(core::string text, core::size_type count) noexcept {
        while (count-- > 0)
            std::fputs(text, stdout);
    }

    auto print(core::string format, ...) noexcept {
        va_list args;
        va_start(args, format);
        std::vprintf(format, args);
        va_end(args);
    }

    auto empty(core::state::assert_struct state) noexcept {
        return state.total == 0;
    }

    auto empty(core::state::object_struct state) noexcept {
        return state.destroyed + state.constructed == 0;
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

    size_type output::indentation = 0;

    output::~output() noexcept {
        ::outdent();
    }

    output::output(string name) noexcept {
        ::repeat(format::space, indentation);
        ::print(format::scope, name);
        ::indent();
    }

    auto output::on_error(string source) noexcept -> void {
        ::repeat(format::space, indentation);
        ::print(format::error, source);
    }

    auto output::on_success(string source) noexcept -> void {
        ::repeat(format::space, indentation);
        ::print(format::success, source);
    }

    auto output::on_exception(string source) noexcept -> void {
        ::repeat(format::space, indentation);
        ::print(format::exception, source);
    }

    auto output::on_unit_error(state result) noexcept -> void {
        if (!::empty(result.assert)) {
            ::repeat(format::space, indentation);
            ::print(format::test_error, result.assert.error, result.assert.total);
        }
        if (!::empty(result.object)) {
            ::repeat(format::space, indentation);
            ::print(format::resource_error, result.object.destroyed, result.object.constructed,
                    result.error.destructor, result.error.constructor, result.error.assignment);
        }
    }

    auto output::on_unit_success(state result) noexcept -> void {
        if (!::empty(result.assert)) {
            ::repeat(format::space, indentation);
            ::print(format::test_success, result.assert.error, result.assert.total);
        }
        if (!::empty(result.object)) {
            ::repeat(format::space, indentation);
            ::print(format::resource_success, result.object.destroyed, result.object.constructed,
                    result.error.destructor, result.error.constructor, result.error.assignment);
        }
    }

}
