#include <output.hpp>
#include <state.hpp>
#include <utility>
#include <cstdio>

namespace {

    using namespace test;
    using namespace test::core;

    struct group {
        struct test;
        struct resource;
    };

    struct msg {
        struct error;
        struct exception;
        struct reserr;
        struct resok;
        struct space;
        struct success;
        struct testerr;
        struct testok;
        struct text;
        struct unit;
    };

    auto indent() noexcept {
        ++output::level;
    }

    auto outdent() noexcept {
        --output::level;
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
    auto print<msg::space> = [](size_type count = output::level) noexcept {
        while (count --> 0)
            std::fputs("  ", stdout);
    };

    template <>
    auto print<msg::text> = [](string format, auto&&... args) noexcept {
        std::fprintf(stdout, format, std::forward<decltype(args)>(args)...);
    };

    template <>
    auto print<msg::unit> = [](string name) noexcept {
        print<msg::space>();
        print<msg::text>("(%sunit%s %s)\n", "\033[93m", "\033[0m", name);
    };

    template <>
    auto print<msg::error> = [](string source) noexcept {
        print<msg::space>();
        print<msg::text>("(%serror%s %s)\n", "\033[31m", "\033[0m", source);
    };

    template <>
    auto print<msg::success> = [](string source) noexcept {
        print<msg::space>();
        print<msg::text>("(%sok%s %s)\n", "\033[32m", "\033[0m", source);
    };

    template <>
    auto print<msg::exception> = [](string source) noexcept {
        print<msg::space>();
        print<msg::text>("(%sexception%s %s)\n", "\033[31m", "\033[0m", source);
    };

    template <>
    auto print<msg::testok> = [](const state_array& data) noexcept {
        if (!empty<group::test>(data)) {
            print<msg::space>();
            print<msg::text>("(%stest ok%s ", "\033[32m", "\033[0m");
            print<msg::text>("[%zu/%zu])\n", data[state::error], data[state::check]);
        }
    };

    template <>
    auto print<msg::testerr> = [](const state_array& data) noexcept {
        if (!empty<group::test>(data)) {
            print<msg::space>();
            print<msg::text>("(%stest error%s ", "\033[31m", "\033[0m");
            print<msg::text>("[%zu/%zu])\n", data[state::error], data[state::check]);
        }
    };

    template <>
    auto print<msg::resok> = [](const state_array& data) noexcept {
        if (!empty<group::resource>(data)) {
            print<msg::space>();
            print<msg::text>("(%sresource ok%s ", "\033[32m", "\033[0m");
            print<msg::text>("[%zu/%zu] ", data[state::dtor], data[state::ctor]);
            print<msg::text>("[%zu/%zu/%zu])\n", data[state::dterr], data[state::cterr], data[state::operr]);
        }
    };

    template <>
    auto print<msg::reserr> = [](const state_array& data) noexcept {
        if (!empty<group::resource>(data)) {
            print<msg::space>();
            print<msg::text>("(%sresource error%s ", "\033[31m", "\033[0m");
            print<msg::text>("[%zu/%zu] ", data[state::dtor], data[state::ctor]);
            print<msg::text>("[%zu/%zu/%zu])\n", data[state::dterr], data[state::cterr], data[state::operr]);
        }
    };

}

namespace test::core {

    size_type output::level = 0;

    output::~output() noexcept {
        if (state.status() && !state.empty()) {
            print<msg::testok>(state.difference());
            print<msg::resok>(state.difference());
            outdent();
        } else if (!state.status()) {
            print<msg::testerr>(state.difference());
            print<msg::reserr>(state.difference());
            outdent();
        }
    }

    output::output(string name, const registry& state) noexcept : state(state) {
        print<msg::unit>(name);
        indent();
    }

    auto output::on_error(string source) noexcept -> void {
        print<msg::error>(source);
    }

    auto output::on_success(string source) noexcept -> void {
        print<msg::success>(source);
    }

    auto output::on_exception(string source) noexcept -> void {
        print<msg::exception>(source);
    }

}
