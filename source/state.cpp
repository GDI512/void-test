#include <state.hpp>
#include <output.hpp>

namespace test {

    auto exit_status() noexcept -> int {
        return core::exit_status;
    }

}

namespace test::core {

    int exit_status = exit_success;

    template <typename T>
    typename static_list<T>::pointer static_list<T>::active_node = nullptr;

    template <typename T>
    static_list<T>::~static_list() noexcept {
        active_node = previous_node;
    }

    template <typename T>
    static_list<T>::static_list() noexcept {
        previous_node = active_node;
        active_node = this;
    }

    template <typename T>
    auto static_list<T>::current() noexcept -> reference {
        return static_cast<T&>(*active_node);
    }

    scope::scope(string name) noexcept : name(name) {
        output::on_scope(name);
    }

    auto scope::data() noexcept -> string {
        return name;
    }

    test_registry::~test_registry() noexcept {
        if (status() && !empty()) {
            output::on_test_registry_success(count);
        } else if (!status()) {
            exit_status = exit_failure;
            output::on_test_registry_error(count);
        }
    }

    test_registry::test_registry() noexcept : count() {}

    auto test_registry::data() const noexcept -> state {
        return count;
    }

    auto test_registry::empty() const noexcept -> bool {
        return count.passed == 0 && count.failed == 0;
    }

    auto test_registry::status() const noexcept -> bool {
        return count.failed == 0;
    }

    auto test_registry::on_error() noexcept -> size_type {
        return count.failed++;
    }

    auto test_registry::on_success() noexcept -> size_type {
        return count.passed++;
    }

    resource_verifier::~resource_verifier() noexcept {
        if (status() && !empty()) {
            output::on_resource_verifier_success(count);
        } else if (!status()) {
            exit_status = exit_failure;
            output::on_resource_verifier_error(count);
        }
    }

    resource_verifier::resource_verifier() noexcept : count() {}

    auto resource_verifier::data() const noexcept -> state {
        return count;
    }

    auto resource_verifier::empty() const noexcept -> bool {
        return count.destroyed == 0 && count.constructed == 0;
    }

    auto resource_verifier::status() const noexcept -> bool {
        return count.destroyed == count.constructed && count.destructor_errors == 0 && count.constructor_errors == 0 &&
               count.operator_errors == 0;
    }

    auto resource_verifier::on_destruction() noexcept -> size_type {
        return count.destroyed++;
    }

    auto resource_verifier::on_construction() noexcept -> size_type {
        return count.constructed++;
    }

    auto resource_verifier::on_destructor_error() noexcept -> size_type {
        return count.destructor_errors++;
    }

    auto resource_verifier::on_constructor_error() noexcept -> size_type {
        return count.constructor_errors++;
    }

    auto resource_verifier::on_operator_error() noexcept -> size_type {
        return count.operator_errors++;
    }

    template class static_list<scope>;
    template class static_list<test_registry>;
    template class static_list<resource_verifier>;

}
