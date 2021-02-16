#include "state.hpp"
#include <output.hpp>
#include <cstdio>

namespace test::core::format {

    constexpr auto space = "  ";
    constexpr auto scope = "(\033[93munit\033[0m %s)\n";
    constexpr auto error = "(\033[31merror\033[0m %s)\n";
    constexpr auto success = "(\033[32mok\033[0m %s)\n";
    constexpr auto exception = "(\033[31mexception\033[0m %s)\n";
    constexpr auto registry_error = "(\033[31mtest error\033[0m [%llu/%llu])\n";
    constexpr auto registry_success = "(\033[32mtest ok\033[0m [%llu/%llu])\n";
    constexpr auto verifier_error = "(\033[31mresource error\033[0m [%llu/%llu] [%llu/%llu/%llu])\n";
    constexpr auto verifier_success = "(\033[32mresource ok\033[0m [%llu/%llu] [%llu/%llu/%llu])\n";

}

namespace test::core {

    size_t indent_level = 0;

    static auto indent() noexcept -> void {
        ++indent_level;
    }

    static auto outdent() noexcept -> void {
        --indent_level;
    }

    static auto repeat(const char* text, size_t count) -> void {
        while (count-- > 0) {
            std::fputs(text, stdout);
        }
    }

    scope::~scope() noexcept {
        outdent();
    }

    scope::scope(const char* name) noexcept {
        repeat(format::space, indent_level);
        std::printf(format::scope, name);
        indent();
    }

    auto scope::on_error(const char* source) noexcept -> void {
        repeat(format::space, indent_level);
        std::printf(format::error, source);
    }

    auto scope::on_success(const char* source) noexcept -> void {
        repeat(format::space, indent_level);
        std::printf(format::success, source);
    }

    auto scope::on_exception(const char* source) noexcept -> void {
        repeat(format::space, indent_level);
        std::printf(format::exception, source);
    }

    auto scope::on_registry_error(test_info state) noexcept -> void {
        repeat(format::space, indent_level);
        std::printf(format::registry_error, state.error_count, state.total_count);
    }

    auto scope::on_registry_success(test_info state) noexcept -> void {
        repeat(format::space, indent_level);
        std::printf(format::registry_success, state.error_count, state.total_count);
    }

    auto scope::on_verifier_error(object_info state) noexcept -> void {
        repeat(format::space, indent_level);
        std::printf(format::verifier_error, state.destroyed_count, state.constructed_count,
                    state.destructor_error_count, state.constructor_error_count, state.operator_error_count);
    }

    auto scope::on_verifier_success(object_info state) noexcept -> void {
        repeat(format::space, indent_level);
        std::printf(format::verifier_success, state.destroyed_count, state.constructed_count,
                    state.destructor_error_count, state.constructor_error_count, state.operator_error_count);
    }

}
