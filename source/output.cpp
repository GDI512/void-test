#include "state.hpp"
#include <output.hpp>
#include <cstdio>

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

namespace test {

    struct test_tag {};
    struct resource_tag {};

    static auto indent() noexcept -> void {
        ++indent_level;
    }

    static auto outdent() noexcept -> void {
        --indent_level;
    }

    static auto empty(state result, test_tag) {
        return result.assert.total == 0;
    }

    static auto empty(state result, resource_tag) {
        return result.object.destroyed == 0 && result.object.constructed == 0;
    }

    static auto repeat(const char* text, size_type count) -> void {
        while (count-- > 0)
            std::fputs(text, stdout);
    }

    output::~output() noexcept {
        test::outdent();
    }

    output::output(const char* name) noexcept {
        test::repeat(format::space, indent_level);
        std::printf(format::scope, name);
        test::indent();
    }

    auto output::on_error(const char* source) noexcept -> void {
        test::repeat(format::space, indent_level);
        std::printf(format::error, source);
    }

    auto output::on_success(const char* source) noexcept -> void {
        test::repeat(format::space, indent_level);
        std::printf(format::success, source);
    }

    auto output::on_exception(const char* source) noexcept -> void {
        test::repeat(format::space, indent_level);
        std::printf(format::exception, source);
    }

    auto output::on_unit_error(state result) noexcept -> void {
        if (!empty(result, test_tag())) {
            test::repeat(format::space, indent_level);
            std::printf(format::test_error, result.assert.error, result.assert.total);
        }
        if (!empty(result, resource_tag())) {
            test::repeat(format::space, indent_level);
            std::printf(format::resource_error, result.object.destroyed, result.object.constructed,
                        result.error.destructor, result.error.constructor, result.error.assignment);
        }
    }

    auto output::on_unit_success(state result) noexcept -> void {
        if (!empty(result, test_tag())) {
            test::repeat(format::space, indent_level);
            std::printf(format::test_success, result.assert.error, result.assert.total);
        }
        if (!empty(result, resource_tag())) {
            test::repeat(format::space, indent_level);
            std::printf(format::resource_success, result.object.destroyed, result.object.constructed,
                        result.error.destructor, result.error.constructor, result.error.assignment);
        }
    }

    size_type indent_level = 0;

}
