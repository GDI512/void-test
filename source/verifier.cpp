#include <verifier.hpp>
#include <output.hpp>
#include <state.hpp>

namespace void_test::core {

    verifier::~verifier() noexcept {
        if (status() && !empty()) {
            output::on_resource_success(test);
        } else if (!status()) {
            exit_code = exit_failure;
            output::on_resource_error(test);
        }
    }

    verifier::verifier() noexcept : test() {}

    auto verifier::data() noexcept -> state {
        return current().test;
    }

    auto verifier::empty() noexcept -> bool {
        return current().test.destroyed_count == 0 && current().test.constructed_count == 0;
    }

    auto verifier::status() noexcept -> bool {
        return current().test.destroyed_count == current().test.constructed_count &&
               current().test.destructor_error_count == 0 && current().test.constructor_error_count == 0 &&
               current().test.operator_error_count == 0;
    }

    auto verifier::on_destruction() noexcept -> size_type {
        return current().test.destroyed_count++;
    }

    auto verifier::on_construction() noexcept -> size_type {
        return current().test.constructed_count++;
    }

    auto verifier::on_destructor_error() noexcept -> size_type {
        return current().test.destructor_error_count++;
    }

    auto verifier::on_constructor_error() noexcept -> size_type {
        return current().test.constructor_error_count++;
    }

    auto verifier::on_operator_error() noexcept -> size_type {
        return current().test.operator_error_count++;
    }

}
