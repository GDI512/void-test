#include <output.hpp>
#include <format.hpp>
#include <state.hpp>
#include <cstdarg>
#include <cstdio>

namespace {

    using namespace test;

    auto indent() noexcept {
        ++core::indentation;
    }

    auto outdent() noexcept {
        --core::indentation;
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

namespace test::core {

    size_type indentation = 0;

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
