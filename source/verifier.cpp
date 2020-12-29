#include <verifier.hpp>
#include <output.hpp>
#include <state.hpp>

namespace void_test::core {

    verifier::~verifier() noexcept {
        if (status() && !empty()) {
            output::on_verifier_success(count);
        } else if (!status()) {
            exit_status = exit_failure;
            output::on_verifier_error(count);
        }
    }

    verifier::verifier() noexcept : count() {}

    auto verifier::data() const noexcept -> state {
        return count;
    }

    auto verifier::empty() const noexcept -> bool {
        return count.destroyed == 0 && count.constructed == 0;
    }

    auto verifier::status() const noexcept -> bool {
        return count.destroyed == count.constructed && count.destructor_errors == 0 && count.constructor_errors == 0 &&
               count.operator_errors == 0;
    }

    auto verifier::on_destruction() noexcept -> size_type {
        return count.destroyed++;
    }

    auto verifier::on_construction() noexcept -> size_type {
        return count.constructed++;
    }

    auto verifier::on_destructor_error() noexcept -> size_type {
        return count.destructor_errors++;
    }

    auto verifier::on_constructor_error() noexcept -> size_type {
        return count.constructor_errors++;
    }

    auto verifier::on_operator_error() noexcept -> size_type {
        return count.operator_errors++;
    }

}
