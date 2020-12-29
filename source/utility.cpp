#include <utility.hpp>
#include <scope.hpp>
#include <registry.hpp>
#include <verifier.hpp>

namespace void_test::core {

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

    template class static_list<scope>;
    template class static_list<registry>;
    template class static_list<verifier>;

}
