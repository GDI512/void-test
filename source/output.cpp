#include <output.hpp>
#include <state.hpp>
#include <iostream>

namespace {

    using namespace test;
    using namespace test::core;

    enum class message { test, resource };

    enum class format { expression, list, newline };

    auto indent() noexcept -> void {
        ++output::level;
    }

    auto outdent() noexcept -> void {
        --output::level;
    }

    auto repeat(size_type count, string text = "  ") noexcept -> void {
        while (count-- > 0)
            std::cout << text;
    }

    auto printable(message type, state_array result) noexcept -> bool {
        switch (type) {
          case message::test:
            return result[state::checks] != 0;
          case message::resource:
            return result[state::destructors] + result[state::constructors] != 0;
          default:
            return false;
        }
    }

    template <typename... T>
    auto print(format style, T&&... arguments) noexcept -> void{
        switch (style) {
          case format::expression:
            std::cout << '(';
            (std::cout << ... << arguments);
            std::cout << ") ";
            break;
          case format::list:
            std::cout << '[';
            (std::cout << ... << arguments);
            std::cout << "] ";
            break;
          case format::newline:
            std::cout << '\n';
            break;
        }
    }

}

namespace test::core {

    size_type output::level = 0;

    output::~output() noexcept {
        outdent();
    }

    output::output(string name) noexcept {
        repeat(level);
        print(format::expression, "\033[93m", "unit", "\033[0m ", name);
        print(format::newline);
        indent();
    }

    auto output::on_error(string source) noexcept -> void {
        repeat(level);
        print(format::expression, "\033[31m", "error", "\033[0m ", source);
        print(format::newline);
    }

    auto output::on_success(string source) noexcept -> void {
        repeat(level);
        print(format::expression, "\033[32m", "ok", "\033[0m ", source);
        print(format::newline);
    }

    auto output::on_exception(string source) noexcept -> void {
        repeat(level);
        print(format::expression, "\033[31m", "exception", "\033[0m ", source);
        print(format::newline);
    }

    auto output::on_unit_error(state_array result) noexcept -> void {
        if (printable(message::test, result)) {
            repeat(level);
            print(format::expression, "\033[31m", "test error", "\033[0m");
            print(format::list, result[state::errors], '/', result[state::checks]);
            print(format::newline);
        }
        if (printable(message::resource, result)) {
            repeat(level);
            print(format::expression, "\033[31m", "resource error", "\033[0m");
            print(format::list, result[state::destructors], '/', result[state::constructors], '/',
                result[state::destructor_errors], '/', result[state::constructor_errors], '/',
                    result[state::assignment_errors]);
            print(format::newline);
        }
    }

    auto output::on_unit_success(state_array result) noexcept -> void {
        if (printable(message::test, result)) {
            repeat(level);
            print(format::expression, "\033[32m", "test ok", "\033[0m");
            print(format::list, result[state::errors], '/', result[state::checks]);
            print(format::newline);
        }
        if (printable(message::resource, result)) {
            repeat(level);
            print(format::expression, "\033[32m", "resource ok", "\033[0m");
            print(format::list, result[state::destructors], '/', result[state::constructors], '/',
                result[state::destructor_errors], '/', result[state::constructor_errors], '/',
                    result[state::assignment_errors]);
            print(format::newline);
        }
    }

}
