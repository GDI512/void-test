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

    auto verifier::data() noexcept -> state {
        return current().count;
    }

    auto verifier::empty() noexcept -> bool {
        return current().count.destroyed == 0 && current().count.constructed == 0;
    }

    auto verifier::status() noexcept -> bool {
        auto& ref = current();
        const auto is_even = ref.count.destroyed == ref.count.constructed;
        const auto is_error_free = ref.count.dtor_errors == 0 && ref.count.ctor_errors == 0 && ref.count.op_errors == 0;
        return is_even && is_error_free;
    }

    auto verifier::on_destruction() noexcept -> size_type {
        return current().count.destroyed++;
    }

    auto verifier::on_construction() noexcept -> size_type {
        return current().count.constructed++;
    }

    auto verifier::on_destructor_error() noexcept -> size_type {
        return current().count.dtor_errors++;
    }

    auto verifier::on_constructor_error() noexcept -> size_type {
        return current().count.ctor_errors++;
    }

    auto verifier::on_operator_error() noexcept -> size_type {
        return current().count.op_errors++;
    }

}
