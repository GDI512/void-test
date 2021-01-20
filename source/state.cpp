#include <state.hpp>
#include <output.hpp>

namespace test::core {

    scope::scope(string name) noexcept : name(name) {
        output::on_scope(name);
    }

    auto scope::data() noexcept -> string {
        return current().name;
    }

    registry::~registry() noexcept {
        if (status() && !empty()) {
            output::on_test_success({error_count, success_count});
        } else if (!status()) {
            global::exit_status(exit_failure);
            output::on_test_error({error_count, success_count});
        }
    }

    registry::registry() noexcept {}

    auto registry::data() noexcept -> registry_state {
        return {current().error_count, current().success_count};
    }

    auto registry::empty() noexcept -> bool {
        return current().success_count == 0 && current().error_count == 0;
    }

    auto registry::status() noexcept -> bool {
        return current().error_count == 0;
    }

    auto registry::on_error(string source) noexcept -> size_type {
        output::on_error(source);
        return current().error_count++;
    }

    auto registry::on_success(string source) noexcept -> size_type {
        output::on_success(source);
        return current().success_count++;
    }

    auto registry::on_exception(string source) noexcept -> size_type {
        output::on_exception(source);
        return current().error_count++;
    }

    verifier::~verifier() noexcept {
        if (status() && !empty()) {
            output::on_resource_success({destroyed_count, constructed_count, destructor_error_count,
                                         constructor_error_count, operator_error_count});
        } else if (!status()) {
            global::exit_status(exit_failure);
            output::on_resource_error({destroyed_count, constructed_count, destructor_error_count,
                                       constructor_error_count, operator_error_count});
        }
    }

    verifier::verifier() noexcept {}

    auto verifier::data() noexcept -> verifier_state {
        return {current().destroyed_count, current().constructed_count, current().destructor_error_count,
                current().constructor_error_count, current().operator_error_count};
    }

    auto verifier::empty() noexcept -> bool {
        return current().destroyed_count == 0 && current().constructed_count == 0;
    }

    auto verifier::status() noexcept -> bool {
        return current().destroyed_count == current().constructed_count && current().destructor_error_count == 0 &&
               current().constructor_error_count == 0 && current().operator_error_count == 0;
    }

    auto verifier::on_destruction() noexcept -> size_type {
        return current().destroyed_count++;
    }

    auto verifier::on_construction() noexcept -> size_type {
        return current().constructed_count++;
    }

    auto verifier::on_destructor_error() noexcept -> size_type {
        return current().destructor_error_count++;
    }

    auto verifier::on_constructor_error() noexcept -> size_type {
        return current().constructor_error_count++;
    }

    auto verifier::on_operator_error() noexcept -> size_type {
        return current().operator_error_count++;
    }

    int global::exit_code = exit_success;

    auto global::exit_status() noexcept -> int {
        return exit_code;
    }

    auto global::exit_status(int code) noexcept -> void {
        exit_code = code;
    }

}
