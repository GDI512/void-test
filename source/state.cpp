#include <state.hpp>
#include <cstdio>

namespace test {

    namespace {

        auto print_space(int count) noexcept {
            while (count --> 0) {
                std::fputc(' ', stdout);
                std::fputc(' ', stdout);
            }
        }

        auto print_unit(string name) noexcept {
            std::fprintf(stdout, "(\033[93munit\033[0m %s)\n", name);
        }

        auto print_error(string source) noexcept {
            std::fprintf(stdout, "(\033[31merror\033[0m %s)\n", source);
        }

        auto print_success(string source) noexcept {
            std::fprintf(stdout, "(\033[32mok\033[0m %s)\n", source);
        }

        auto print_exception() noexcept {
            std::fprintf(stdout, "(\033[31mexception\033[0m)\n");
        }

        auto print_test_error(int error_count, int check_count) noexcept {
            std::fprintf(stdout, "(\033[31mtest error\033[0m [%i/%i])\n", error_count, check_count);
        }

        auto print_test_success(int error_count, int check_count) noexcept {
            std::fprintf(stdout, "(\033[32mtest ok\033[0m [%i/%i])\n", error_count, check_count);
        }

        auto print_resource_error(int destroyed_count, int constructed_count,
                int destructor_error_count, int constructor_error_count, int operator_error_count) noexcept {
            std::fprintf(stdout, "(\033[31mresource error\033[0m [%i/%i] [%i/%i/%i])\n", destroyed_count,
                constructed_count, destructor_error_count, constructor_error_count, operator_error_count);
        }

        auto print_resource_success(int destroyed_count, int constructed_count,
                int destructor_error_count, int constructor_error_count, int operator_error_count) noexcept {
            std::fprintf(stdout, "(\033[32mresource ok\033[0m [%i/%i] [%i/%i/%i])\n", destroyed_count,
                constructed_count, destructor_error_count, constructor_error_count, operator_error_count);
        }

        auto is_test_printable(int check_count) noexcept {
            return check_count != 0;
        }

        auto is_resource_printable(int destroyed_count, int constructed_count, int operator_error_count) noexcept {
            return destroyed_count + constructed_count + operator_error_count != 0;
        }

    }

    int output::level = {};

    output::~output() noexcept {
        --level;
    }

    output::output(string name) noexcept {
        print_space(level);
        print_unit(name);
        ++level;
    }

    auto output::on_error(string source) noexcept -> void {
        print_space(level);
        print_error(source);
    }

    auto output::on_success(string source) noexcept -> void {
        print_space(level);
        print_success(source);
    }

    auto output::on_exception() noexcept -> void {
        print_space(level);
        print_exception();
    }

    auto output::on_rollback(state snapshot, bool is_ok) noexcept -> void {
        if (is_ok) {
            if (is_test_printable(snapshot.check_count)) {
                print_space(level);
                print_test_success(snapshot.error_count, snapshot.check_count);
            }
            if (is_resource_printable(snapshot.destroyed_count,
                    snapshot.constructed_count, snapshot.operator_error_count)) {
                print_space(level);
                print_resource_success(snapshot.destroyed_count, snapshot.constructed_count,
                    snapshot.destructor_error_count, snapshot.constructor_error_count,
                            snapshot.operator_error_count);
            }
        } else {
            if (is_test_printable(snapshot.check_count)) {
                print_space(level);
                print_test_error(snapshot.error_count, snapshot.check_count);
            }
            if (is_resource_printable(snapshot.destroyed_count,
                    snapshot.constructed_count, snapshot.operator_error_count)) {
                print_space(level);
                print_resource_error(snapshot.destroyed_count, snapshot.constructed_count,
                    snapshot.destructor_error_count, snapshot.constructor_error_count,
                            snapshot.operator_error_count);
            }
        }
    }

    int state::code = exit_success;

    state state::global = {};

    auto state::operator-(state other) noexcept -> state {
        auto result = state();
        result.error_count = this->error_count - other.error_count;
        result.check_count = this->check_count - other.check_count;
        result.destroyed_count = this->destroyed_count - other.destroyed_count;
        result.constructed_count = this->constructed_count - other.constructed_count;
        result.destructor_error_count = this->destructor_error_count - other.destructor_error_count;
        result.constructor_error_count = this->constructor_error_count - other.constructor_error_count;
        result.operator_error_count = this->operator_error_count - other.operator_error_count;
        return result;
    }

    auto state::operator-=(state other) noexcept -> state& {
        this->error_count -= other.error_count;
        this->check_count -= other.check_count;
        this->destroyed_count -= other.destroyed_count;
        this->constructed_count -= other.constructed_count;
        this->destructor_error_count -= other.destructor_error_count;
        this->constructor_error_count -= other.constructor_error_count;
        this->operator_error_count -= other.operator_error_count;
        return *this;
    }

    auto state::is_ok() noexcept -> bool {
        return error_count == 0 && destroyed_count == constructed_count &&
            destructor_error_count + constructor_error_count + operator_error_count == 0;
    }

    auto state::is_empty() noexcept -> bool {
        return error_count + check_count == 0 && destroyed_count + constructed_count == 0 &&
            destructor_error_count + constructor_error_count + operator_error_count == 0;
    }

    auto state::get() noexcept -> state {
        return global;
    }

    auto state::on_exit() noexcept -> int {
        return code;
    }

    auto state::on_exit(int value) noexcept -> void {
        code = value;
    }

    auto state::on_error() noexcept -> void {
        ++global.error_count;
        ++global.check_count;
        code = exit_failure;
    }

    auto state::on_success() noexcept -> void {
        ++global.check_count;
    }

    auto state::on_exception() noexcept -> void {
        ++global.error_count;
        code = exit_failure;
    }

    auto state::on_destruction() noexcept -> void {
        ++global.destroyed_count;
    }

    auto state::on_construction() noexcept -> void {
        ++global.constructed_count;
    }

    auto state::on_destructor_error() noexcept -> void {
        ++global.destructor_error_count;
        code = exit_failure;
    }

    auto state::on_constructor_error() noexcept -> void {
        ++global.constructor_error_count;
        code = exit_failure;
    }

    auto state::on_operator_error() noexcept -> void {
        ++global.operator_error_count;
        code = exit_failure;
    }

    auto state::on_rollback(state result) noexcept -> void {
        global -= result;
    }

    registry::~registry() noexcept {
        const auto result = state::get() - snapshot;
        if (is_ok() && !is_empty()) {
            state::on_rollback(result);
            output::on_rollback(result, true);
        } else if (!is_ok()) {
            state::on_rollback(result);
            output::on_rollback(result, false);
        }
    }

    registry::registry(string scope) noexcept : snapshot(state::get()), printer(scope) {}

    auto registry::is_ok() noexcept -> bool {
        return (state::get() - snapshot).is_ok();
    }

    auto registry::is_empty() noexcept -> bool {
        return (state::get() - snapshot).is_empty();
    }

    auto registry::on_exit() noexcept -> int {
        return state::on_exit();
    }

    auto registry::on_error(string source) noexcept -> bool {
        state::on_error();
        output::on_error(source);
        return false;
    }

    auto registry::on_success(string source) noexcept -> bool {
        state::on_success();
        output::on_success(source);
        return true;
    }

    auto registry::on_exception() noexcept -> void {
        state::on_exception();
        output::on_exception();
    }

    auto registry::on_destruction() noexcept -> void {
        state::on_destruction();
    }

    auto registry::on_construction() noexcept -> void {
        state::on_construction();
    }

    auto registry::on_destructor_error() noexcept -> void {
        state::on_destructor_error();
    }

    auto registry::on_constructor_error() noexcept -> void {
        state::on_constructor_error();
    }

    auto registry::on_operator_error() noexcept -> void {
        state::on_operator_error();
    }

}
