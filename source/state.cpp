#include <state.hpp>
#include <cstdarg>
#include <cstdio>

namespace {

    using namespace test;

    enum class message {
        unit,
        unit_error,
        unit_success,
        test_error,
        test_success,
        resource_error,
        resource_success,
        error,
        success,
        exception,
        destructor,
        constructor,
        destructor_error,
        constructor_error,
        operator_error
    };

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

    auto is_ok(state::test data) noexcept {
        return data.error_count == 0;
    }

    auto is_ok(state::resource data) noexcept {
        return data.destructor_count == data.constructor_count &&
            data.destructor_error_count + data.constructor_error_count + data.operator_error_count == 0;
    }

    auto is_empty(state::test data) noexcept {
        return data.total_count + data.error_count == 0;
    }

    auto is_empty(state::resource data) noexcept {
        return data.destructor_count + data.constructor_count == 0 &&
            data.destructor_error_count + data.constructor_error_count + data.operator_error_count == 0;
    }

    auto output(string format, ...) noexcept {
        va_list args;
        for (auto count = scope_level; count > 0; count--)
            std::fputs("  ", stdout);
        va_start(args, format);
        std::vprintf(format, args);
        va_end(args);
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

    template <message select>
    auto report() noexcept = delete;

    template <>
    auto report<message::error>() noexcept {
        global.check.error_count++;
        global.check.total_count++;
    }

    template <>
    auto report<message::success>() noexcept {
        global.check.total_count++;
    }

    template <>
    auto report<message::exception>() noexcept {
        global.check.error_count++;
    }

    template <>
    auto report<message::destructor>() noexcept {
        global.object.destructor_count++;
    }

    template <>
    auto report<message::constructor>() noexcept {
        global.object.constructor_count++;
    }

    template <>
    auto report<message::destructor_error>() noexcept {
        global.object.destructor_error_count++;
    }

    template <>
    auto report<message::constructor_error>() noexcept {
        global.object.constructor_error_count++;
    }

    template <>
    auto report<message::operator_error>() noexcept {
        global.object.operator_error_count++;
    }

    template <message select>
    auto print() noexcept = delete;

    template <message select>
    auto print(string) noexcept = delete;

    template <message select>
    auto print(state::test) noexcept = delete;

    template <message select>
    auto print(state::resource) noexcept = delete;

    template <>
    auto print<message::unit>(string name) noexcept {
        output(format<message::unit>, name);
    };

    template <>
    auto print<message::error>(string source) noexcept {
        output(format<message::error>, source);
    };

    template <>
    auto print<message::success>(string source) noexcept {
        output(format<message::success>, source);
    };

    template <>
    auto print<message::exception>() noexcept {
         output(format<message::exception>);
    };

    template <>
    auto print<message::unit_error>(state::test data) noexcept {
        if (!is_ok(data)) {
            output(format<message::test_error>, data.error_count, data.total_count);
        }
    };

    template <>
    auto print<message::unit_success>(state::test data) noexcept {
        if (is_ok(data) && !is_empty(data)) {
            output(format<message::test_success>, data.error_count, data.total_count);
        }
    };

    template <>
    auto print<message::unit_error>(state::resource data) noexcept {
        if (!is_ok(data)) {
            output(format<message::resource_error>, data.destructor_count, data.constructor_count,
                data.destructor_error_count, data.constructor_error_count, data.operator_error_count);
        }
    };

    template <>
    auto print<message::unit_success>(state::resource data) noexcept {
        if (is_ok(data) && !is_empty(data)) {
            output(format<message::resource_success>, data.destructor_count, data.constructor_count,
                data.destructor_error_count, data.constructor_error_count, data.operator_error_count);
        }
    };

}

namespace test {

    state global = {};
    integer exit_code = exit_success;
    integer scope_level = {};

    registry::~registry() noexcept {
        const auto result = difference();
        if (ok() && !empty()) {
            print<message::unit_success>(result.check);
            print<message::unit_success>(result.object);
            restore();
        } else if (!ok()) {
            print<message::unit_error>(result.check);
            print<message::unit_error>(result.object);
            restore();
            exit_code = exit_failure;
        }
    }

    registry::registry(string scope) noexcept {
        print<message::unit>(scope);
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
        const auto result = difference();
        return is_ok(result.check) && is_ok(result.object);
    }

    auto registry::empty() const noexcept -> bool {
        const auto result = difference();
        return is_empty(result.check) && is_empty(result.object);
    }

    auto registry::difference() const noexcept -> state {
        return global - snapshot;
    }

    auto on_error(string source) noexcept -> bool {
        report<message::error>();
        print<message::error>(source);
        return false;
    }

    auto on_success(string source) noexcept -> bool {
        report<message::success>();
        print<message::success>(source);
        return true;
    }

    auto on_exception() noexcept -> void {
        report<message::exception>();
        print<message::exception>();
    }

    auto on_destructor() noexcept -> void {
        report<message::destructor>();
    }

    auto on_constructor() noexcept -> void {
        report<message::constructor>();
    }

    auto on_destructor_error() noexcept -> void {
        report<message::destructor_error>();
    }

    auto on_constructor_error() noexcept -> void {
        report<message::constructor_error>();
    }

    auto on_operator_error() noexcept -> void {
        report<message::operator_error>();
    }

}
