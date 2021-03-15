#include <state.hpp>
#include <cstdio>

namespace test {

    int scope_nesting = 0;

    namespace {

        auto good(state::test data) noexcept {
            return data.error_count == 0;
        }

        auto good(state::resource data) noexcept {
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

        auto operator-(state::test left, state::test right) noexcept {
            auto result = state::test();
            result.error_count = left.error_count - right.error_count;
            result.total_count = left.total_count - right.total_count;
            return result;
        }

        auto operator-(state::resource left, state::resource right) noexcept {
            auto result = state::resource();
            result.destructor_count = left.destructor_count - right.destructor_count;
            result.constructor_count = left.constructor_count - right.constructor_count;
            result.destructor_error_count = left.destructor_error_count - right.destructor_error_count;
            result.constructor_error_count = left.constructor_error_count - right.constructor_error_count;
            result.operator_error_count = left.operator_error_count - right.operator_error_count;
            return result;
        }

        auto operator-(state left, state right) noexcept {
            auto result = state();
            result.check = left.check - right.check;
            result.object = left.object - right.object;
            return result;
        }

    }

    int registry::exit = exit_success;

    state registry::global = {};

    registry::~registry() noexcept {
        const auto data = result();
        if (good() && !empty()) {
            print_unit_success(data.check);
            print_unit_success(data.object);
            restore();
        } else if (!good()) {
            print_unit_error(data.check);
            print_unit_error(data.object);
            restore();
            exit = exit_failure;
        }
    }

    registry::registry(string scope) noexcept {
        print_unit(scope);
        save();
    }

    auto registry::good() const noexcept -> bool {
        using test::good;
        const auto data = result();
        return good(data.check) && good(data.object);
    }

    auto registry::empty() const noexcept -> bool {
        using test::empty;
        const auto data = result();
        return empty(data.check) && empty(data.object);
    }

    auto registry::result() const noexcept -> state {
        return global - snapshot;
    }

    auto registry::save() noexcept -> void {
        snapshot = global;
        scope_nesting++;
    }

    auto registry::restore() noexcept -> void {
        global = snapshot;
        scope_nesting--;
    }

    auto on_exit() noexcept -> int {
        return registry::exit;
    }

    auto on_error(string source) noexcept -> bool {
        report_error();
        print_error(source);
        return false;
    }

    auto on_success(string source) noexcept -> bool {
        report_success();
        print_success(source);
        return true;
    }

    auto on_exception(string source) noexcept -> void {
        report_success();
        print_success(source);
    }

    auto on_destruction() noexcept -> void {
        report_destruction();
    }

    auto on_construction() noexcept -> void {
        report_construction();
    }

    auto on_destructor_error() noexcept -> void {
        report_destructor_error();
    }

    auto on_constructor_error() noexcept -> void {
        report_constructor_error();
    }

    auto on_operator_error() noexcept -> void {
        report_operator_error();
    }

    auto report_error() noexcept -> void {
        registry::global.check.error_count++;
        registry::global.check.total_count++;
    }

    auto report_success() noexcept -> void {
        registry::global.check.total_count++;
    }

    auto report_exception() noexcept -> void {
        registry::global.check.error_count++;
    }

    auto report_destruction() noexcept -> void {
        registry::global.object.destructor_count++;
    }

    auto report_construction() noexcept -> void {
        registry::global.object.constructor_count++;
    }

    auto report_destructor_error() noexcept -> void {
        registry::global.object.destructor_error_count++;
    }

    auto report_constructor_error() noexcept -> void {
        registry::global.object.constructor_error_count++;
    }

    auto report_operator_error() noexcept -> void {
        registry::global.object.operator_error_count++;
    }

    auto print_unit(string name) noexcept -> void {
        for (auto level = 0; level < scope_nesting; level++)
            std::fputs("  ", stdout);
        std::fprintf(stdout, "(\033[93munit\033[0m %s)\n", name);
    }

    auto print_error(string source) noexcept -> void {
        for (auto level = 0; level < scope_nesting; level++)
            std::fputs("  ", stdout);
        std::fprintf(stdout, "(\033[31merror\033[0m %s)\n", source);
    }

    auto print_success(string source) noexcept -> void {
        for (auto level = 0; level < scope_nesting; level++)
            std::fputs("  ", stdout);
        std::fprintf(stdout, "(\033[32mok\033[0m %s)\n", source);
    }

    auto print_exception(string source) noexcept -> void {
        for (auto level = 0; level < scope_nesting; level++)
            std::fputs("  ", stdout);
        std::fprintf(stdout, "(\033[31mexception\033[0m %s)\n", source);
    }

    auto print_unit_error(state::test data) noexcept -> void {
        if (!good(data)) {
            for (auto level = 0; level < scope_nesting; level++)
                std::fputs("  ", stdout);
            std::fprintf(stdout, "(\033[31mtest error\033[0m [%i/%i])\n", data.error_count, data.total_count);
        }
    }

    auto print_unit_success(state::test data) noexcept -> void {
        if (good(data) && !empty(data)) {
            for (auto level = 0; level < scope_nesting; level++)
                std::fputs("  ", stdout);
            std::fprintf(stdout, "(\033[32mtest ok\033[0m [%i/%i])\n", data.error_count, data.total_count);
        }
    }

    auto print_unit_error(state::resource data) noexcept -> void {
        if (!good(data)) {
            for (auto level = 0; level < scope_nesting; level++)
                std::fputs("  ", stdout);
            std::fprintf(stdout, "(\033[31mresource error\033[0m [%i/%i] [%i/%i/%i])\n", data.destructor_count,
                data.constructor_count, data.destructor_error_count, data.constructor_error_count,
                    data.operator_error_count);
        }
    }

    auto print_unit_success(state::resource data) noexcept -> void {
        if (good(data) && !empty(data)) {
            for (auto level = 0; level < scope_nesting; level++)
                std::fputs("  ", stdout);
            std::fprintf(stdout, "(\033[32mresource ok\033[0m [%i/%i] [%i/%i/%i])\n", data.destructor_count,
                data.constructor_count, data.destructor_error_count, data.constructor_error_count,
                    data.operator_error_count);
        }
    }

}
