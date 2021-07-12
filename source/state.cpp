#include "state.hpp"

#include <cstdarg>
#include <cstdio>

namespace test {

    int exit_code = {};
    int indent_count = {};

    unit_state* unit_state::current = nullptr;

    unit_state::~unit_state() noexcept {
        if (!good()) {
            print_unit_error(get());
            current = previous;
            exit_code = 1;
        } else if (!empty()) {
            print_unit_success(get());
            current = previous;
        }
    }

    unit_state::unit_state(string name) noexcept : previous(current), snapshot() {
        print_unit(name);
        current = this;
    }

    auto unit_state::active() noexcept -> unit_state& {
        return *current;
    }

    auto unit_state::on_error(string check) noexcept -> bool {
        print_error(check);
        snapshot.error_count++;
        snapshot.check_count++;
        return false;
    }

    auto unit_state::on_success(string check) noexcept -> bool {
        print_success(check);
        snapshot.check_count++;
        return true;
    }

    auto unit_state::on_exception() noexcept -> void {
        print_exception();
        snapshot.error_count++;
    }

    auto unit_state::on_destruction() noexcept -> void {
        snapshot.destroyed_count++;
    }

    auto unit_state::on_construction() noexcept -> void {
        snapshot.constructed_count++;
    }

    auto unit_state::get() const noexcept -> state {
        return snapshot;
    }

    auto unit_state::good() const noexcept -> bool {
        return snapshot.error_count == 0 && snapshot.destroyed_count == snapshot.constructed_count;
    }

    auto unit_state::empty() const noexcept -> bool {
        return snapshot.check_count + snapshot.error_count +
            snapshot.destroyed_count + snapshot.constructed_count == 0;
    }

    auto print(string format, ...) noexcept -> void {
        va_list args;
        for (auto level = 0; level < indent_count; level++)
            fputs("  ", stdout);
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
    }

    auto print_unit(string name) noexcept -> void {
        print("(\033[93munit\033[0m %s)\n", name);
        indent_count++;
    }

    auto print_error(string source) noexcept -> void {
        print("(\033[31merror\033[0m %s)\n", source);
    }

    auto print_success(string source) noexcept -> void {
        print("(\033[32mok\033[0m %s)\n", source);
    }

    auto print_exception() noexcept -> void {
        print("(\033[31mexception\033[0m)\n");
    }

    auto print_unit_error(unit_state::state result) noexcept -> void {
        print("(\033[31mtest error\033[0m [%i/%i] [%i/%i])\n", result.error_count, result.check_count,
          result.destroyed_count, result.constructed_count);
    }

    auto print_unit_success(unit_state::state result) noexcept -> void {
        print("(\033[32mtest ok\033[0m [%i/%i] [%i/%i])\n", result.error_count, result.check_count,
          result.destroyed_count, result.constructed_count);
    }

}
