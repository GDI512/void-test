#include <state.hpp>
#include <scope.hpp>
#include <registry.hpp>
#include <verifier.hpp>

namespace void_test {

    auto exit_status() noexcept -> int {
        return core::exit_code;
    }

}

namespace void_test::core {

    int exit_code = exit_success;

    template <typename T>
    static_list<T>* static_list<T>::active_node = nullptr;

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
    auto static_list<T>::current() noexcept -> T& {
        return static_cast<T&>(*active_node);
    }

    template class static_list<scope>;
    template class static_list<registry>;
    template class static_list<verifier>;

}
