#include <state.hpp>
#include <output.hpp>

namespace void_test::core {

    scope::scope(string name) noexcept : name(name) {
        output::on_scope(name);
    }

    auto scope::data() noexcept -> string {
        return current().name;
    }

    registry::~registry() noexcept {
        if (status() && !empty()) {
            output::on_test_success(info);
        } else if (!status()) {
            global::exit_status(exit_failure);
            output::on_test_error(info);
        }
    }

    registry::registry() noexcept : info() {}

    auto registry::data() noexcept -> state {
        return current().info;
    }

    auto registry::empty() noexcept -> bool {
        return current().info.success_count == 0 && current().info.error_count == 0;
    }

    auto registry::status() noexcept -> bool {
        return current().info.error_count == 0;
    }

    auto registry::on_error(string source) noexcept -> size_type {
        output::on_error(source);
        return current().info.error_count++;
    }

    auto registry::on_success(string source) noexcept -> size_type {
        output::on_success(source);
        return current().info.success_count++;
    }

    auto registry::on_exception(string source) noexcept -> size_type {
        output::on_exception(source);
        return current().info.error_count++;
    }

    verifier::~verifier() noexcept {
        if (status() && !empty()) {
            output::on_resource_success(info);
        } else if (!status()) {
            global::exit_status(exit_failure);
            output::on_resource_error(info);
        }
    }

    verifier::verifier() noexcept : info() {}

    auto verifier::data() noexcept -> state {
        return current().info;
    }

    auto verifier::empty() noexcept -> bool {
        return current().info.destroyed_count == 0 && current().info.constructed_count == 0;
    }

    auto verifier::status() noexcept -> bool {
        return current().info.destroyed_count == current().info.constructed_count &&
               current().info.destructor_error_count == 0 && current().info.constructor_error_count == 0 &&
               current().info.operator_error_count == 0;
    }

    auto verifier::on_destruction() noexcept -> size_type {
        return current().info.destroyed_count++;
    }

    auto verifier::on_construction() noexcept -> size_type {
        return current().info.constructed_count++;
    }

    auto verifier::on_destructor_error() noexcept -> size_type {
        return current().info.destructor_error_count++;
    }

    auto verifier::on_constructor_error() noexcept -> size_type {
        return current().info.constructor_error_count++;
    }

    auto verifier::on_operator_error() noexcept -> size_type {
        return current().info.operator_error_count++;
    }

    auto global::exit_code = exit_success;

    auto global::exit_status() noexcept -> int {
        return exit_code;
    }

    auto global::exit_status(int code) noexcept -> void {
        exit_code = code;
    }

}
