#include <output.hpp>
#include <cstdio>

namespace test::core::format {

    constexpr auto space = "  ";
    constexpr auto scope = "(unit %s)\n";
    constexpr auto error = "(error %s)\n";
    constexpr auto success = "(ok %s)\n";
    constexpr auto exception = "(exception %s)\n";
    constexpr auto registry_error = "(test error [%iu/%iu])\n";
    constexpr auto registry_success = "(test ok [%iu/%iu])\n";
    constexpr auto verifier_error = "(resource error [%iu/%iu] [%iu/%iu/%iu])\n";
    constexpr auto verifier_success = "(resource ok [%iu/%iu] [%iu/%iu/%iu])\n";

}

namespace test::core {

    size_type indent_level = 0;

    static auto indent() noexcept -> void {
        ++indent_level;
    }

    static auto outdent() noexcept -> void {
        --indent_level;
    }

    static auto repeat(string text, size_type count) -> void {
        while (count-- > 0) {
            std::fputs(text, stdout);
        }
    }

    scope::~scope() noexcept {
        outdent();
    }

    scope::scope(string name) noexcept {
        repeat(format::space, indent_level);
        printf(format::scope, name);
        indent();
    }

    auto print_error(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::error, source);
    }

    auto print_success(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::success, source);
    }

    auto print_exception(string source) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::exception, source);
    }

    auto print_registry_error(test_state state) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::registry_error, state.error_count, state.total_count);
    }

    auto print_registry_success(test_state state) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::registry_success, state.error_count, state.total_count);
    }

    auto print_verifier_error(resource_state state) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::verifier_error, state.destroyed_count, state.constructed_count, state.destructor_error_count,
               state.constructor_error_count, state.operator_error_count);
    }

    auto print_verifier_success(resource_state state) noexcept -> void {
        repeat(format::space, indent_level);
        printf(format::verifier_success, state.destroyed_count, state.constructed_count, state.destructor_error_count,
               state.constructor_error_count, state.operator_error_count);
    }

}
