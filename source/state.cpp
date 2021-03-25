#include <state.hpp>
#include <cstdarg>
#include <cstdio>

namespace {

    using namespace test;

    auto ok(state::test data) noexcept {
        return data.error_count == 0;
    }

    auto ok(state::resource data) noexcept {
        return data.destructor_count == data.constructor_count &&
            data.destructor_error_count + data.constructor_error_count + data.operator_error_count == 0;
    }

    auto empty(state::test data) noexcept {
        return data.total_count + data.error_count == 0;
    }

    auto empty(state::resource data) noexcept {
        return data.destructor_count + data.constructor_count == 0 &&
            data.destructor_error_count + data.constructor_error_count + data.operator_error_count == 0;
    }

    auto print(string format, ...) noexcept {
        va_list args;
        va_start(args, format);
        std::vprintf(format, args);
        va_end(args);
    }

    auto repeat(string text, integer count) noexcept {
        while (count --> 0)
            std::fputs(text, stdout);
    }

    auto add_error() noexcept {
        global.check.error_count++;
        global.check.total_count++;
    }

    auto add_success() noexcept {
        global.check.total_count++;
    }

    auto add_exception() noexcept {
        global.check.error_count++;
    }

    auto add_destructor() noexcept {
        global.object.destructor_count++;
    }

    auto add_constructor() noexcept {
        global.object.constructor_count++;
    }

    auto add_destructor_error() noexcept {
        global.object.destructor_error_count++;
    }

    auto add_constructor_error() noexcept {
        global.object.constructor_error_count++;
    }

    auto add_operator_error() noexcept {
        global.object.operator_error_count++;
    }

    auto print_unit(string name) noexcept {
        repeat("  ", scope_level);
        print("(\033[93munit\033[0m %s)\n", name);
    }

    auto print_error(string source) noexcept {
        repeat("  ", scope_level);
        print("(\033[31merror\033[0m %s)\n", source);
    }

    auto print_success(string source) noexcept {
        repeat("  ", scope_level);
        print("(\033[32mok\033[0m %s)\n", source);
    }

    auto print_exception() noexcept {
        repeat("  ", scope_level);
        print("(\033[31mexception\033[0m)\n");
    }

    auto print_unit_error(state::test data) noexcept {
        if (!ok(data)) {
            repeat("  ", scope_level);
            print("(\033[31mtest error\033[0m [%i/%i])\n", data.error_count, data.total_count);
        }
    }

    auto print_unit_success(state::test data) noexcept {
        if (ok(data) && !empty(data)) {
            repeat("  ", scope_level);
            print("(\033[32mtest ok\033[0m [%i/%i])\n", data.error_count, data.total_count);
        }
    }

    auto print_unit_error(state::resource data) noexcept {
        if (!ok(data)) {
            repeat("  ", scope_level);
            print("(\033[31mresource error\033[0m [%i/%i] ", data.destructor_count, data.constructor_count);
            print("[%i/%i/%i])\n", data.destructor_error_count, data.constructor_error_count, data.operator_error_count);
        }
    }

    auto print_unit_success(state::resource data) noexcept {
        if (ok(data) && !empty(data)) {
            repeat("  ", scope_level);
            print("(\033[32mresource ok\033[0m [%i/%i] ", data.destructor_count, data.constructor_count);
            print("[%i/%i/%i])\n", data.destructor_error_count, data.constructor_error_count, data.operator_error_count);
        }
    }

    auto operator-(state::test left, state::test right) noexcept {
        return state::test {
            left.error_count - right.error_count,
            left.total_count - right.total_count
        };
    }

    auto operator-(state::resource left, state::resource right) noexcept {
        return state::resource {
            left.destructor_count - right.destructor_count,
            left.constructor_count - right.constructor_count,
            left.destructor_error_count - right.destructor_error_count,
            left.constructor_error_count - right.constructor_error_count,
            left.operator_error_count - right.operator_error_count
        };
    }

    auto operator-(state left, state right) noexcept {
        return state {
            left.check - right.check,
            left.object - right.object
        };
    }

}

namespace test {

    integer exit_code = exit_success;

    integer scope_level = {};

    state global = {};

    registry::~registry() noexcept {
        const auto diff = difference();
        if (ok() && !empty()) {
            print_unit_success(diff.check);
            print_unit_success(diff.object);
            restore();
        } else if (!ok()) {
            print_unit_error(diff.check);
            print_unit_error(diff.object);
            restore();
            exit_code = exit_failure;
        }
    }

    registry::registry(string scope) noexcept {
        print_unit(scope);
        save();
    }

    auto registry::save() noexcept -> void {
        snapshot = global;
        scope_level++;
    }

    auto registry::restore() noexcept -> void {
        global = snapshot;
        scope_level--;
    }

    auto registry::ok() const noexcept -> bool {
        const auto data = difference();
        return ::ok(data.check) && ::ok(data.object);
    }

    auto registry::empty() const noexcept -> bool {
        const auto data = difference();
        return ::empty(data.check) && ::empty(data.object);
    }

    auto registry::difference() const noexcept -> state {
        return global - snapshot;
    }

    auto on_exit() noexcept -> integer {
        return exit_code;
    }

    auto on_error(string source) noexcept -> bool {
        add_error();
        print_error(source);
        return false;
    }

    auto on_success(string source) noexcept -> bool {
        add_success();
        print_success(source);
        return true;
    }

    auto on_exception() noexcept -> void {
        add_exception();
        print_exception();
    }

    auto on_destructor() noexcept -> void {
        add_destructor();
    }

    auto on_constructor() noexcept -> void {
        add_constructor();
    }

    auto on_destructor_error() noexcept -> void {
        add_destructor_error();
    }

    auto on_constructor_error() noexcept -> void {
        add_constructor_error();
    }

    auto on_operator_error() noexcept -> void {
        add_operator_error();
    }

}
