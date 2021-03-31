// ========================== output.cpp ==========================
//
//  Part of the cppltf library, under the BSD-3-Clause License.
//  See https://github.com/GDI512/cppltf/blob/master/LICENSE for
//  license information.
//
// ================================================================

#include <output.hpp>
#include <state.hpp>
#include <cstdarg>
#include <cstdio>

namespace format {

    constexpr auto unit = "(\033[93munit\033[0m %s)\n";

    constexpr auto error = "(\033[31merror\033[0m %s)\n";

    constexpr auto success = "(\033[32mok\033[0m %s)\n";

    constexpr auto exception = "(\033[31mexception\033[0m)\n";

    constexpr auto test_error = "(\033[31mtest error\033[0m [%i/%i])\n";

    constexpr auto test_success = "(\033[32mtest ok\033[0m [%i/%i])\n";

    constexpr auto resource_error = "(\033[31mresource error\033[0m [%i/%i] [%i/%i/%i])\n";

    constexpr auto resource_success = "(\033[32mresource ok\033[0m [%i/%i] [%i/%i/%i])\n";

}

namespace test {

    integer scope_level = {};

    template <>
    auto display<message::unit>(string name) noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        std::printf(format::unit, name);
    }

    template <>
    auto display<message::error>(string source) noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        std::printf(format::error, source);
    }

    template <>
    auto display<message::success>(string source) noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        std::printf(format::success, source);
    }

    template <>
    auto display<message::exception>() noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
         std::printf(format::exception);
    }

    template <>
    auto display<message::unit_error>(state::test data) noexcept -> void {
        if (!is_ok(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf(format::test_error, data.error_count, data.total_count);
        }
    }

    template <>
    auto display<message::unit_success>(state::test data) noexcept -> void {
        if (is_ok(data) && !is_empty(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf(format::test_success, data.error_count, data.total_count);
        }
    }

    template <>
    auto display<message::unit_error>(state::resource data) noexcept -> void {
        if (!is_ok(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf(format::resource_error, data.destructor_count, data.constructor_count,
                data.destructor_error_count, data.constructor_error_count, data.operator_error_count);
        }
    }

    template <>
    auto display<message::unit_success>(state::resource data) noexcept -> void {
        if (is_ok(data) && !is_empty(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf(format::resource_success, data.destructor_count, data.constructor_count,
                data.destructor_error_count, data.constructor_error_count, data.operator_error_count);
        }
    }

}
