#include <output.hpp>
#include <format.hpp>
#include <state.hpp>
#include <cstdarg>
#include <cstdio>

namespace {

    using namespace test;

    struct test_tag {};
    struct resource_tag {};

    auto indent() noexcept {
        ++aux::indentation;
    }

    auto outdent() noexcept {
        --aux::indentation;
    }

    auto repeat(const char* text, aux::size_type count) noexcept {
        while (count-- > 0)
            std::fputs(text, stdout);
    }

    auto print(const char* format, ...) noexcept {
        va_list args;
        va_start(args, format);
        std::vprintf(format, args);
        va_end(args);
    }

    constexpr auto empty(aux::state state, test_tag) noexcept {
        return state.assert.total == 0;
    }

    constexpr auto empty(aux::state state, resource_tag) noexcept {
        return state.object.destroyed + state.object.constructed == 0;
    }

}

namespace test::aux {

    size_type indentation = 0;

    output::~output() noexcept {
        ::outdent();
    }

    output::output(const char* name) noexcept {
        ::repeat(format::space, indentation);
        ::print(format::scope, name);
        ::indent();
    }

    auto output::on_error(const char* source) noexcept -> void {
        ::repeat(format::space, indentation);
        ::print(format::error, source);
    }

    auto output::on_success(const char* source) noexcept -> void {
        ::repeat(format::space, indentation);
        ::print(format::success, source);
    }

    auto output::on_exception(const char* source) noexcept -> void {
        ::repeat(format::space, indentation);
        ::print(format::exception, source);
    }

    auto output::on_unit_error(state result) noexcept -> void {
        if (!::empty(result, test_tag())) {
            ::repeat(format::space, indentation);
            ::print(format::test_error, result.assert.error, result.assert.total);
        }
        if (!::empty(result, resource_tag())) {
            ::repeat(format::space, indentation);
            ::print(format::resource_error, result.object.destroyed, result.object.constructed,
                    result.error.destructor, result.error.constructor, result.error.assignment);
        }
    }

    auto output::on_unit_success(state result) noexcept -> void {
        if (!::empty(result, test_tag())) {
            ::repeat(format::space, indentation);
            ::print(format::test_success, result.assert.error, result.assert.total);
        }
        if (!::empty(result, resource_tag())) {
            ::repeat(format::space, indentation);
            ::print(format::resource_success, result.object.destroyed, result.object.constructed,
                    result.error.destructor, result.error.constructor, result.error.assignment);
        }
    }

}
