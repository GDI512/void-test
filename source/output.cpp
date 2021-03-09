#include <output.hpp>
#include <state.hpp>
#include <cstdio>

namespace {

    using namespace test;
    using namespace test::core;

    struct group {
        struct test {};
        struct resource {};
    };

    struct format {
        struct unit {};
        struct error {};
        struct success {};
        struct exception {};
        struct test_ok {};
        struct resource_ok {};
        struct test_error {};
        struct resource_error {};
    };

    auto indent() noexcept {
        ++output::level;
    }

    auto outdent() noexcept {
        --output::level;
    }

    auto repeat(size_type count, string text = "  ") noexcept {
        while (count --> 0)
            std::fputs(text, stdout);
    }

    template <typename select>
    auto empty = 0;

    template <>
    auto empty<group::test> = [](const state_array& data) noexcept {
        return data[state::check] == 0;
    };

    template <>
    auto empty<group::resource> = [](const state_array& data) noexcept {
        return data[state::dtor] + data[state::ctor] + data[state::operr] == 0;
    };

    template <typename select>
    auto print = 0;

    template <>
    auto print<format::unit> = [](string name) noexcept {
        ::repeat(output::level);
        std::printf("(%sunit%s %s)\n", "\033[93m", "\033[0m", name);
    };

    template <>
    auto print<format::error> = [](string source) noexcept {
        ::repeat(output::level);
        std::printf("(%serror%s %s)\n", "\033[31m", "\033[0m", source);
    };

    template <>
    auto print<format::success> = [](string source) noexcept {
        ::repeat(output::level);
        std::printf("(%sok%s %s)\n", "\033[32m", "\033[0m", source);
    };

    template <>
    auto print<format::exception> = [](string source) noexcept {
        ::repeat(output::level);
        std::printf("(%sexception%s %s)\n", "\033[31m", "\033[0m", source);
    };

    template <>
    auto print<format::test_ok> = [](const state_array& data) noexcept {
        if (!empty<group::test>(data)) {
            ::repeat(output::level);
            std::printf("(%stest ok%s ", "\033[32m", "\033[0m");
            std::printf("[%zu/%zu])\n", data[state::error], data[state::check]);
        }
    };

    template <>
    auto print<format::test_error> = [](const state_array& data) noexcept {
        if (!empty<group::test>(data)) {
            ::repeat(output::level);
            std::printf("(%stest error%s ", "\033[31m", "\033[0m");
            std::printf("[%zu/%zu])\n", data[state::error], data[state::check]);
        }
    };

    template <>
    auto print<format::resource_ok> = [](const state_array& data) noexcept {
        if (!empty<group::resource>(data)) {
            ::repeat(output::level);
            std::printf("(%sresource ok%s ", "\033[32m", "\033[0m");
            std::printf("[%zu/%zu] ", data[state::dtor], data[state::ctor]);
            std::printf("[%zu/%zu/%zu])\n", data[state::dterr], data[state::cterr], data[state::operr]);
        }
    };

    template <>
    auto print<format::resource_error> = [](const state_array& data) noexcept {
        if (!empty<group::resource>(data)) {
            ::repeat(output::level);
            std::printf("(%sresource error%s ", "\033[31m", "\033[0m");
            std::printf("[%zu/%zu] ", data[state::dtor], data[state::ctor]);
            std::printf("[%zu/%zu/%zu])\n", data[state::dterr], data[state::cterr], data[state::operr]);
        }
    };

}

namespace test::core {

    size_type output::level = 0;

    output::~output() noexcept {
        if (state.status() && !state.empty()) {
            ::print<format::test_ok>(state.difference());
            ::print<format::resource_ok>(state.difference());
            ::outdent();
        } else if (!state.status()) {
            ::print<format::test_error>(state.difference());
            ::print<format::resource_error>(state.difference());
            ::outdent();
        }
    }

    output::output(string name, const registry& state) noexcept : state(state) {
        ::print<format::unit>(name);
        ::indent();
    }

    auto output::on_error(string source) noexcept -> void {
        ::print<format::error>(source);
    }

    auto output::on_success(string source) noexcept -> void {
        ::print<format::success>(source);
    }

    auto output::on_exception(string source) noexcept -> void {
        ::print<format::exception>(source);
    }

}
