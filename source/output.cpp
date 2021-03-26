#include <output.hpp>
#include <state.hpp>
#include <cstdarg>
#include <cstdio>

namespace {

    using namespace test;

    template <message select>
    constexpr auto format = nullptr;

    template <>
    constexpr auto format<message::unit> = "(\033[93munit\033[0m %s)\n";

    template <>
    constexpr auto format<message::error> = "(\033[31merror\033[0m %s)\n";

    template <>
    constexpr auto format<message::success> = "(\033[32mok\033[0m %s)\n";

    template <>
    constexpr auto format<message::exception> = "(\033[31mexception\033[0m)\n";

    template <>
    constexpr auto format<message::test_error> = "(\033[31mtest error\033[0m [%i/%i])\n";

    template <>
    constexpr auto format<message::test_success> = "(\033[32mtest ok\033[0m [%i/%i])\n";

    template <>
    constexpr auto format<message::resource_error> = "(\033[31mresource error\033[0m [%i/%i] [%i/%i/%i])\n";

    template <>
    constexpr auto format<message::resource_success> = "(\033[32mresource ok\033[0m [%i/%i] [%i/%i/%i])\n";

}

namespace test {

    integer scope_level = {};

    template <>
    auto print<message::unit>(string name) noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        std::printf(format<message::unit>, name);
    }

    template <>
    auto print<message::error>(string source) noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        std::printf(format<message::error>, source);
    }

    template <>
    auto print<message::success>(string source) noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        std::printf(format<message::success>, source);
    }

    template <>
    auto print<message::exception>() noexcept -> void {
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
         std::printf(format<message::exception>);
    }

    template <>
    auto print<message::unit_error>(state::test data) noexcept -> void {
        if (!status(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf(format<message::test_error>, data.error_count, data.total_count);
        }
    }

    template <>
    auto print<message::unit_success>(state::test data) noexcept -> void {
        if (status(data) && !empty(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf(format<message::test_success>, data.error_count, data.total_count);
        }
    }

    template <>
    auto print<message::unit_error>(state::resource data) noexcept -> void {
        if (!status(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf(format<message::resource_error>, data.destructor_count, data.constructor_count,
                data.destructor_error_count, data.constructor_error_count, data.operator_error_count);
        }
    }

    template <>
    auto print<message::unit_success>(state::resource data) noexcept -> void {
        if (status(data) && !empty(data)) {
            for (auto count = scope_level; count > 0; count--)
                std::fputs("  ", stdout);
            std::printf(format<message::resource_success>, data.destructor_count, data.constructor_count,
                data.destructor_error_count, data.constructor_error_count, data.operator_error_count);
        }
    }

}
