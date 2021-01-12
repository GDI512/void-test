#include <utility.hpp>
#include <state.hpp>

namespace void_test::core {

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

    template <typename T>
    auto static_list<T>::is_linked() noexcept -> bool {
        return active_node != nullptr && active_node->previous_node != nullptr;
    }

    template class static_list<scope>;
    template class static_list<registry>;
    template class static_list<verifier>;

}
