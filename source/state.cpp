#include <state.hpp>
#include <output.hpp>

namespace test::core {

    template <typename T>
    typename auto_node<T>::pointer auto_node<T>::active = nullptr;

    template <typename T>
    auto_node<T>::~auto_node() noexcept {
        active = previous;
    }

    template <typename T>
    auto_node<T>::auto_node() noexcept {
        previous = active;
        active = this;
    }

    template <typename T>
    auto auto_node<T>::current() noexcept -> reference {
        return static_cast<T&>(*active);
    }

    scope::scope(string info) noexcept : info(info) {
        output::on_scope(info);
    }

    auto scope::data() noexcept -> state {
        return info;
    }

    registry::~registry() noexcept {
        if (!empty()) {
            if (status()) {
                output::on_registry_success(info);
            } else {
                output::on_registry_error(info);
            }
        }
    }

    registry::registry() noexcept : info() {}

    auto registry::data() const noexcept -> state {
        return info;
    }

    auto registry::empty() const noexcept -> bool {
        return info.passed == 0 && info.failed == 0;
    }

    auto registry::status() const noexcept -> bool {
        return info.failed == 0;
    }

    auto registry::on_error() noexcept -> size_type {
        return current().info.failed++;
    }

    auto registry::on_success() noexcept -> size_type {
        return current().info.passed++;
    }

    verifier::~verifier() noexcept {
        if (!empty()) {
            if (status()) {
                output::on_verifier_success(info);
            } else {
                output::on_verifier_error(info);
            }
        }
    }

    verifier::verifier() noexcept : info() {}

    auto verifier::data() const noexcept -> state {
        return info;
    }

    auto verifier::empty() const noexcept -> bool {
        return info.destroyed == 0 && info.constructed == 0;
    }

    auto verifier::status() const noexcept -> bool {
        return info.destroyed == info.constructed && info.destructor_errors == 0 && info.constructor_errors == 0 &&
               info.operator_errors == 0;
    }

    auto verifier::on_destruction() noexcept -> size_type {
        return current().info.destroyed++;
    }

    auto verifier::on_contruction() noexcept -> size_type {
        return current().info.constructed++;
    }

    auto verifier::on_destructor_error() noexcept -> size_type {
        return current().info.destructor_errors++;
    }

    auto verifier::on_constructor_error() noexcept -> size_type {
        return current().info.constructor_errors++;
    }

    auto verifier::on_operator_error() noexcept -> size_type {
        return current().info.operator_errors++;
    }

    template class auto_node<scope>;
    template class auto_node<registry>;
    template class auto_node<verifier>;

}
