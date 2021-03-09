#include <output.hpp>
#include <state.hpp>
#include <iostream>

namespace {

    using namespace test;
    using namespace test::core;

    struct color {
        static constexpr auto red = "\033[31m";
        static constexpr auto green = "\033[32m";
        static constexpr auto yellow = "\033[93m";
        static constexpr auto reset = "\033[0m";
    };

    auto indent() noexcept -> void {
        ++output::level;
    }

    auto outdent() noexcept -> void {
        --output::level;
    }

    auto insert_spaces() noexcept -> void {
        for (auto count = output::level; count > 0; count--)
            std::cout << "  ";
    }

    auto print_unit(string name) noexcept -> void {
        std::cout << '(' << color::yellow << "unit " << color::reset << name << ")\n";
    };

    auto print_error(string source) noexcept -> void {
        std::cout << '(' << color::red << "error " << color::reset << source << ")\n";
    };

    auto print_success(string source) noexcept -> void {
        std::cout << '(' << color::green << "ok " << color::reset << source << ")\n";
    };

    auto print_exception(string source) noexcept -> void {
        std::cout << '(' << color::red << "exception " << color::reset << source << ")\n";
    };

    auto print_test_error(state_array result) noexcept -> void {
        std::cout << '(' << color::red << "test error " << color::reset;
        std::cout << '[' << result[state::errors] << '/' << result[state::checks] << ']';
        std::cout << ")\n";
    }

    auto print_test_success(state_array result) noexcept -> void {
        std::cout << '(' << color::green << "test ok " << color::reset;
        std::cout << '[' << result[state::errors] << '/' << result[state::checks] << ']';
        std::cout << ")\n";
    }

    auto print_resource_error(state_array result) noexcept -> void {
        std::cout << '(' << color::red << "resource error " << color::reset;
        std::cout << '[' << result[state::destructors] << '/' << result[state::constructors] << "] ";
        std::cout << '[' << result[state::destructor_errors] << '/' << result[state::constructor_errors];
        std::cout << '/' << result[state::assignment_errors] << ']';
        std::cout << ")\n";
    }

    auto print_resource_success(state_array result) noexcept -> void {
        std::cout << '(' << color::green << "resource ok " << color::reset;
        std::cout << '[' << result[state::destructors] << '/' << result[state::constructors] << "] ";
        std::cout << '[' << result[state::destructor_errors] << '/' << result[state::constructor_errors];
        std::cout << '/' << result[state::assignment_errors] << ']';
        std::cout << ")\n";
    }

    auto print_exit_error(state_array result) {
        if (result[state::checks] != 0) {
            insert_spaces();
            print_test_error(result);
        }
        if (result[state::destructors] + result[state::constructors] + result[state::assignment_errors] != 0) {
            insert_spaces();
            print_resource_error(result);
        }
    }

    auto print_exit_success(state_array result) {
        if (result[state::checks] != 0) {
            insert_spaces();
            print_test_success(result);
        }
        if (result[state::destructors] + result[state::constructors] + result[state::assignment_errors] != 0) {
            insert_spaces();
            print_resource_success(result);
        }
    }

}

namespace test::core {

    size_type output::level = 0;

    output::~output() noexcept {
        if (state.status() && !state.empty()) {
            print_exit_success(state.diff());
            outdent();
        } else if (!state.status() && !state.empty()) {
            print_exit_error(state.diff());
            outdent();
        }
    }

    output::output(string name, const registry& state) noexcept : state(state) {
        insert_spaces();
        print_unit(name);
        indent();
    }

    auto output::on_error(string source) noexcept -> void {
        insert_spaces();
        print_error(source);
    }

    auto output::on_success(string source) noexcept -> void {
        insert_spaces();
        print_success(source);
    }

    auto output::on_exception(string source) noexcept -> void {
        insert_spaces();
        print_exception(source);
    }

}
