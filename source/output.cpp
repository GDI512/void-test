// ========================== output.cpp ==========================
//
//  Part of the citrine library, under the BSD-3-Clause License.
//  See https://github.com/GDI512/citrine/blob/master/LICENSE for
//  license information.
//
// ================================================================

#include <private/output.hpp>
#include <private/state.hpp>

#include <cstdarg>
#include <cstdio>

namespace test {

    integer scope_level = {};

    template <>
    auto display<message::unit>(string name) noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        std::printf("(\033[93munit\033[0m %s)\n", name);
    }

    template <>
    auto display<message::error>(string source) noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        std::printf("(\033[31merror\033[0m %s)\n", source);
    }

    template <>
    auto display<message::success>(string source) noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        std::printf("(\033[32mok\033[0m %s)\n", source);
    }

    template <>
    auto display<message::exception>() noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
         std::printf("(\033[31mexception\033[0m)\n");
    }

    template <>
    auto display<message::unit_error>(state::test data) noexcept -> void {
        if (!is_ok(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf("(\033[31mtest error\033[0m [%i/%i])\n", data.error_count, data.total_count);
        }
    }

    template <>
    auto display<message::unit_success>(state::test data) noexcept -> void {
        if (is_ok(data) && !is_empty(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf("(\033[32mtest ok\033[0m [%i/%i])\n", data.error_count, data.total_count);
        }
    }

    template <>
    auto display<message::unit_error>(state::resource data) noexcept -> void {
        if (!is_ok(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf("(\033[31mresource error\033[0m [%i/%i] [%i/%i/%i])\n", data.destructor_count,
                data.constructor_count, data.destructor_error_count, data.constructor_error_count,
                    data.operator_error_count);
        }
    }

    template <>
    auto display<message::unit_success>(state::resource data) noexcept -> void {
        if (is_ok(data) && !is_empty(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf("(\033[32mresource ok\033[0m [%i/%i] [%i/%i/%i])\n", data.destructor_count,
                data.constructor_count, data.destructor_error_count, data.constructor_error_count,
                    data.operator_error_count);
        }
    }

}
