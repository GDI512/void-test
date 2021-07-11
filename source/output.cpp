#include "utility.hpp"
#include "output.hpp"
#include "state.hpp"

#include <cstdarg>
#include <cstdio>

namespace {

    using namespace test;

    auto output(string format, ...) noexcept {
        va_list args;
        for (auto level = 0; level < indent; level++)
            fputs("  ", stdout);
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
    }

}

namespace test {

    int indent = {};

    template <>
    auto print<message::unit>(string name) noexcept -> void {
        output("(\033[93munit\033[0m %s)\n", name);
        indent++;
    }

    template <>
    auto print<message::error>(string source) noexcept -> void {
        output("(\033[31merror\033[0m %s)\n", source);
    }

    template <>
    auto print<message::success>(string source) noexcept -> void {
        output("(\033[32mok\033[0m %s)\n", source);
    }

    template <>
    auto print<message::exception>(string source) noexcept -> void {
        output("(\033[31mexception\033[0m %s)\n", source);
    }

    template <>
    auto print<message::error>(state data) noexcept -> void {
        output("(\033[31mtest error\033[0m [%i/%i] [%i/%i])\n", data.error_count, data.total_count,
          data.destroyed_count, data.constructed_count);
    }

    template <>
    auto print<message::success>(state data) noexcept -> void {
        output("(\033[32mtest ok\033[0m [%i/%i] [%i/%i])\n", data.error_count, data.total_count,
          data.destroyed_count, data.constructed_count);
    }

}
